/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:44:10 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/15 20:57:34 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool all_ate(t_philo *philos, int count)
{
	int i;
	t_bool all_ate;

	if (philos->must_eat == -1)
		return (FALSE);
	i = 0;
	all_ate = TRUE;
	while (i < count)
	{
		pthread_mutex_lock(philos->resources.meal_lock);
		if (philos[i].has_eaten < philos[i].must_eat)
			all_ate = FALSE;
		pthread_mutex_unlock(philos->resources.meal_lock);
		i++;
	}
	if (all_ate)
		return (TRUE);
	return (FALSE);
}

void *waiter_work(void *arg)
{
	t_dinner *dinner;
	t_philo *philos;
	int i;

	dinner = (t_dinner *)arg;
	philos = dinner->philos;
	while (TRUE)
	{
		i = 0;
		while (i < dinner->args.number_of_philos)
		{
			pthread_mutex_lock(dinner->meal_lock);
			if (philo_starved(philos[i]))
			{
				pthread_mutex_unlock(dinner->meal_lock);
				pthread_mutex_lock(dinner->dead_lock);
				dinner->somebody_die = TRUE;
				pthread_mutex_unlock(dinner->dead_lock);
				pthread_mutex_lock(dinner->write_lock);
				printf("%ld %d %s\n",
					ft_time_now() - philos[i].born_at,
					philos[i].id, DEATH_LOG);
				pthread_mutex_unlock(dinner->write_lock);
				return (NULL);
			}
			pthread_mutex_unlock(dinner->meal_lock);
			i++;
		}
		if (all_ate(philos, dinner->args.number_of_philos))
		{
			pthread_mutex_lock(dinner->dead_lock);
			dinner->somebody_die = TRUE;
			pthread_mutex_unlock(dinner->dead_lock);
			return (NULL);
		}
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
