/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:33:15 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 14:24:09 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H
# define BAD_ARGUMENT_ERROR 011
# define MEMORY_ALLOC_ERROR 021
# include <stdlib.h>
# include <unistd.h>

typedef struct s_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
}	t_args;

t_args	get_args(int argc, const char *argv[]);
int		validate_args(t_args args);
void	handler_error(int error, const char *message);
#endif