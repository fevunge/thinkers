/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_is_digit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:31:52 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 14:52:01 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	is_digit(unsigned char c)
{
	return (c <= '9' && c >= '0');
}

t_bool	ft_s_is_digit(const char *message)
{
	int	i;

	i = 0;
	if (!message)
		return (FALSE);
	while (message[i])
	{
		if (!is_digit(message[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
