/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:33:02 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 14:53:37 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/philo.h"
#define ARGUMENT_ERROR_MESSAGE "Program must take between 4 or 5 arguments:\n \
- number_of_philosophers\n \
- time_to_die\n \
- time_to_eat\n \
- time_to_sleep\n \
- [number_of_times_each_philosopher_must_eat]\n"

static int	get_argument(const char *arg)
{
	size_t	arg_len;

	arg_len = string_len(arg);
	if (arg_len > 10)
		handler_error(BAD_ARGUMENT_ERROR, "Arguments must be a valid integer");
	return (string_to_int(arg));
}

t_args	get_args(int argc, const char *argv[])
{
	t_args	args;

	if (((argc - 1) / 2) != 2)
		handler_error(BAD_ARGUMENT_ERROR, ARGUMENT_ERROR_MESSAGE);
	args.number_of_philosophers = get_argument(argv[0]);
	args.number_of_philosophers = get_argument(argv[1]);
	args.time_to_eat = get_argument(argv[2]);
	args.time_to_sleep = get_argument(argv[3]);
	if (argc == 5)
		args.times_must_eat = get_argument(argv[4]);
	else
		args.times_must_eat = -1;
	return (args);
}
