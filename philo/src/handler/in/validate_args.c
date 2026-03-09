/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:46:37 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 14:54:41 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/philo.h"
#define ERROR_MESSAGE "The program expects one or more philosophers."

int	validate_args(t_args args)
{
	if (args.number_of_philosophers < 1)
		handler_error(BAD_ARGUMENT_ERROR, ERROR_MESSAGE);
	return (0);
}
