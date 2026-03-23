/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:29:48 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/16 08:41:21 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static t_bool	has_started_simulation(t_philo *philo)
{
	t_bool	started;

	pthread_mutex_lock(philo->start_lock);
	started = *philo->start_simulation;
	pthread_mutex_unlock(philo->start_lock);
	return (started);
}

void	*philo_start_launch(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!has_started_simulation(philo))
		ft_usleep(1);
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!has_dead_philo(philo))
	{
		philo_launch(philo);
		get_log(philo, SLEEP_LOG);
		ft_usleep(philo->sleep);
		get_log(philo, THINK_LOG);
	}
	return (NULL);
}

void	philo_launch(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    get_log(philo, TAKE_FORK_LOG);

    if (philo->left_fork == philo->right_fork)
    {
        // Único filósofo: não tem segundo garfo, espera e morre
        ft_usleep(philo->die * 2);
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }

    pthread_mutex_lock(philo->right_fork);
    get_log(philo, TAKE_FORK_LOG);

    pthread_mutex_lock(philo->meal_lock);
    get_log(philo, EAT_LOG);
    philo->has_eaten++;
    philo->last_meal = ft_time_now();
    pthread_mutex_unlock(philo->meal_lock);

    ft_usleep(philo->eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

t_bool	philo_starved(t_philo *philo)
{
	t_milisecond	time_without_eat;

	time_without_eat = ft_time_now() - philo->last_meal;
	return (time_without_eat > philo->die);
}

t_bool	has_dead_philo(t_philo *philo)
{
	t_bool	dead;

	pthread_mutex_lock(philo->death_lock);
	dead = *philo->somebody_die;
	pthread_mutex_unlock(philo->death_lock);
	return (dead);
}
