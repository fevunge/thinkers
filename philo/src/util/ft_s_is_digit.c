/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_is_digit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:31:52 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 19:34:20 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static t_bool is_digit(unsigned char c)
{
	return (c <= '9' && c >= '0');
}


t_bool	ft_s_is_digit(const char *message)
{
	if (!message)
		return (FALSE);
	while (*message)
	{
		message++;
		if (!is_digit(*message))
			return (FALSE);
	}
	return (TRUE);
}