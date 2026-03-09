/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:54:14 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 14:53:12 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static t_bool	is_space(unsigned char c)
{
	if (c == 32)
		return (1);
	return (c <= 13 && c >= 9);
}

static t_bool	is_signal(unsigned char c)
{
	return (c == SIGNAL_PLUS || c == SIGNAL_MINUS);
}

static t_bool	is_digit(unsigned char c)
{
	return (c <= '9' && c >= '0');
}

int	string_to_int(const char *str)
{
	int			number;
	t_signal	sign;

	sign = 1;
	number = 0;
	while (is_space((unsigned char)*str))
		str++;
	if (is_signal(*str))
	{
		sign = *str - 44;
		str++;
	}
	while (is_digit((unsigned char)*str))
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return ((int)(sign * number));
}
