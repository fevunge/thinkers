/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:50:15 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 14:54:48 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/philo.h"

void	handler_error(int error, const char *message)
{
	if (error == BAD_ARGUMENT_ERROR)
		write(2, "THE ARGUMENTS ARE NOT VALIDS\n", 30);
	write(2, message, string_len(message));
	exit(1);
}
