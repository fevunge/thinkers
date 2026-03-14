/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:42:01 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 14:07:59 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_log(t_philo *philo, const char *log_message)
{
	t_milisecond	age;

	pthread_mutex_lock(philo->resources.write_lock);
	age = ft_time_now() - philo->born_at;
	printf("%ld %d %s\n", age, philo->id, log_message);
	pthread_mutex_unlock(philo->resources.write_lock);
	return ;
}
