/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:33:02 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 20:36:05 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

#define ARG_1_ERROR_MSG "- number_of_philosophers [0 > and <= 200][integer]\n"
#define ARG_2_ERROR_MSG "- time_to_die [integer]\n"
#define ARG_3_ERROR_MSG "- time_to_eat [integer]\n"
#define ARG_4_ERROR_MSG "- time_to_sleep [integer]\n"
#define ARGC_ERROR_MSG "Program must take between 4 or 5 arguments:\n"

static t_bool is_valid_arg(const char *arg)
{
	
}

static int get_argument(const char *argv[], int arg_id)
{
	size_t arg_len;

	if (is_valid_arg(argv[arg_id]))
		get_error(ARGUMENT_ERROR, ARG_1_ERROR_MSG);
	return (ft_atoi(argv[arg_id]));
}

static t_bool validate_args(t_args args)
{
	if (args.number_of_philosophers < 1)
		get_error(ARGUMENT_ERROR, ARG_1_ERROR_MSG);
	return (0);
}

t_args get_args(int argc, const char *argv[])
{
	t_args args;

	args.number_of_philosophers = get_argument(argv, 0);
	args.number_of_philosophers = get_argument(argv, 1);
	args.time_to_eat = get_argument(argv, 2);
	args.time_to_sleep = get_argument(argv, 3);
	if (argc == 5)
		args.times_must_eat = get_argument(argv, 4);
	else
		args.times_must_eat = -1;
	validate_args(args);
	return (args);
}
