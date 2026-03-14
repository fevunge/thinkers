/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:44:10 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 14:20:13 by fevunge          ###   ########.fr       */
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
		if (philos[i].eaten < philos[i].must_eat)
			all_ate = FALSE;
		pthread_mutex_unlock(philos->resources.meal_lock);
		i++;
	}
	if (all_ate)
		return (TRUE);
	return (FALSE);
}

void	*waiter_work(void *arg)
{
	t_dinner	*dinner;
	t_philo		*philos;
	int			i;

	dinner = (t_dinner *)arg;
	philos = dinner->philos;
	while (TRUE)
	{
		i = 0;
		while (i < dinner->args.number_of_philos)
		{
			pthread_mutex_lock(philos[i].resources.meal_lock);
			if (philo_starved(philos[i]))
			{
				pthread_mutex_unlock(philos[i].resources.meal_lock);
				pthread_mutex_lock(philos[i].resources.write_lock);
				printf("%ld %d %s\n",
					ft_time_now() - philos[i].born_at,
					philos[i].id, DEATH_LOG);
				return (NULL);
			}
			pthread_mutex_unlock(philos[i].resources.meal_lock);
			i++;
		}
		if (all_ate(philos, dinner->args.number_of_philos))
		{
			pthread_mutex_lock(philos[0].resources.write_lock);
			return (NULL);
		}
	}
	return (NULL);
}

t_waiter *call_waiter(t_dinner *dinner)
{
	t_waiter *waiter;

	waiter = malloc(sizeof(t_waiter) * 1);
	if (!waiter)
		finish_dinner(dinner);
	if (pthread_create(&waiter->thread_id, NULL, &waiter_work, dinner) != 0)
		finish_dinner(dinner);
	return (waiter);
}
