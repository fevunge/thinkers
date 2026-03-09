/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:54:17 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 14:51:45 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

size_t	string_len(const char *str)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}
