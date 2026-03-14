/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_now.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:58:18 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 13:34:18 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_milisecond	ft_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		get_error(UKNOW_ERROR, "Error getting time from gettimeofday() func\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
