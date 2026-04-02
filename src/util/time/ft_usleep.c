/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:16:17 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 13:31:34 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker.h"

void	ft_usleep(t_milisecond mls)
{
	t_milisecond	start;

	start = ft_time_now();
	while (ft_time_now() - start < mls)
		usleep(500);
}
