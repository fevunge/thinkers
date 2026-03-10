/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:55:03 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 18:35:48 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char const *argv[])
{
	t_args		arguments;
	t_philo		*philos;
	t_dinner	dinner;

	arguments = get_args(argc, argv);
	validate_args(arguments);
	dinner.args = arguments;
	call_philos_to_dinner(philos, &dinner);
	start_dinner(&dinner);
	finish_dinner(&dinner);
	return (0);
}
