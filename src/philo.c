/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:29:48 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/16 08:41:21 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker.h"

void	call_philos_to_dinner(t_dinner *dinner)
{
	int	id;
	int	philos_len;

	id = 0;
	philos_len = dinner->args.philos_n;
	while (id < philos_len)
	{
		dinner->philos[id].id = id + 1;
		dinner->philos[id].die = dinner->args.time_to_die;
		dinner->philos[id].eat = dinner->args.time_to_eat;
		dinner->philos[id].sleep = dinner->args.time_to_sleep;
		dinner->philos[id].must_eat = dinner->args.times_must_eat;
		dinner->philos[id].has_eaten = 0;
		dinner->philos[id].left_fork = dinner->forks + id;
		if (id == 0)
			dinner->philos[id].right_fork = dinner->forks + philos_len - 1;
		else
			dinner->philos[id].right_fork = dinner->forks + id - 1;
		dinner->philos[id].write_lock = dinner->write_lock;
		dinner->philos[id].meal_lock = dinner->meal_lock;
		dinner->philos[id].death_lock = dinner->death_lock;
		dinner->philos[id].start_lock = dinner->start_lock;
		dinner->philos[id].somebody_die = &dinner->somebody_die;
		dinner->philos[id].start_simulation = &dinner->start_simulation;
		id++;
	}
	return ;
}

static t_bool	has_started_simulation(t_thinker *thinker)
{
	t_bool	started;

	pthread_mutex_lock(thinker->start_lock);
	started = *thinker->start_simulation;
	pthread_mutex_unlock(thinker->start_lock);
	return (started);
}

void	*philo_start_launch(void *arg)
{
	t_thinker		*thinker;

	thinker = (t_thinker *)arg;
	while (!has_started_simulation(thinker))
		ft_usleep(1);
	if (thinker->id % 2 == 0)
		ft_usleep(1);
	while (!has_dead_philo(thinker))
	{
		philo_launch(thinker);
		get_log(thinker, SLEEP_LOG);
		ft_usleep(thinker->sleep);
		get_log(thinker, THINK_LOG);
	}
	return (NULL);
}

void	philo_launch(t_thinker *thinker)
{
    pthread_mutex_lock(thinker->left_fork);
    get_log(thinker, TAKE_FORK_LOG);

    if (thinker->left_fork == thinker->right_fork)
    {
        // Único filósofo: não tem segundo garfo, espera e morre
        ft_usleep(thinker->die * 2);
        pthread_mutex_unlock(thinker->left_fork);
        return ;
    }

    pthread_mutex_lock(thinker->right_fork);
    get_log(thinker, TAKE_FORK_LOG);

    pthread_mutex_lock(thinker->meal_lock);
    get_log(thinker, EAT_LOG);
    thinker->has_eaten++;
    thinker->last_meal = ft_time_now();
    pthread_mutex_unlock(thinker->meal_lock);

    ft_usleep(thinker->eat);
    pthread_mutex_unlock(thinker->left_fork);
    pthread_mutex_unlock(thinker->right_fork);
}

t_bool	philo_starved(t_thinker *thinker)
{
	t_milisecond	time_without_eat;

	time_without_eat = ft_time_now() - thinker->last_meal;
	return (time_without_eat > thinker->die);
}

t_bool	has_dead_philo(t_thinker *thinker)
{
	t_bool	dead;

	pthread_mutex_lock(thinker->death_lock);
	dead = *thinker->somebody_die;
	pthread_mutex_unlock(thinker->death_lock);
	return (dead);
}
