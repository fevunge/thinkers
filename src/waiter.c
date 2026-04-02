/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:44:10 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/16 08:44:34 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	has_started_simulation(t_dinner *dinner)
{
	t_bool	started;

	pthread_mutex_lock(dinner->start_lock);
	started = dinner->start_simulation;
	pthread_mutex_unlock(dinner->start_lock);
	return (started);
}

t_bool	all_ate(t_philo *philos, int count)
{
	int		i;
	t_bool	all_ate;

	if (philos->must_eat == -1)
		return (FALSE);
	i = 0;
	all_ate = TRUE;
	while (i < count)
	{
		pthread_mutex_lock(philos->meal_lock);
		if (philos[i].has_eaten < philos[i].must_eat)
			all_ate = FALSE;
		pthread_mutex_unlock(philos->meal_lock);
		i++;
	}
	if (all_ate)
		return (TRUE);
	return (FALSE);
}

static void	announce_death(t_dinner *dinner, t_philo philo)
{
	pthread_mutex_lock(dinner->death_lock);
	dinner->somebody_die = TRUE;
	pthread_mutex_unlock(dinner->death_lock);
	pthread_mutex_lock(dinner->write_lock);
	printf("%ld %d %s\n",
		ft_time_now() - philo.born_at,
		philo.id, DEATH_LOG);
	pthread_mutex_unlock(dinner->write_lock);
}

static void	announce_all_ate(t_dinner *dinner)
{
	pthread_mutex_lock(dinner->death_lock);
	dinner->somebody_die = TRUE;
	pthread_mutex_unlock(dinner->death_lock);
}

void	*waiter_work(void *arg)
{
	t_dinner	*dinner;
	t_philo		*philos;
	int			i;

	dinner = (t_dinner *)arg;
	philos = dinner->philos;
	while (!has_started_simulation(dinner))
		usleep(500);
	while (TRUE)
	{
		i = 0;
		while (i < dinner->args.philos_n)
		{
			pthread_mutex_lock(dinner->meal_lock);
			if (philo_starved(&philos[i]))
			{
				pthread_mutex_unlock(dinner->meal_lock);
				return (announce_death(dinner, philos[i]), NULL);
			}
			pthread_mutex_unlock(dinner->meal_lock);
			i++;
		}
		if (all_ate(philos, dinner->args.philos_n))
			return (announce_all_ate(dinner), NULL);
	}
	return (NULL);
}

void	call_waiter(t_dinner *dinner)
{
	pthread_t	waiter;

	if (pthread_create(&waiter, NULL, &waiter_work, dinner) != 0)
		finish_dinner(dinner);
	dinner->waiter = waiter;
	return ;
}
