/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:42:01 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/16 08:03:58 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_log(t_philo *philo, const char *log_message)
{
	t_milisecond	age;

	pthread_mutex_lock(philo->death_lock);
	if (*philo->somebody_die)
	{
		pthread_mutex_unlock(philo->death_lock);
		return ;
	}
	pthread_mutex_lock(philo->write_lock);
	age = ft_time_now() - philo->born_at;
	printf("%ld %d %s\n", age, philo->id, log_message);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->death_lock);
	return ;
}
