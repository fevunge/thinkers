/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:55:03 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 13:37:47 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const *argv[])
{
	t_dinner	dinner;

	dinner.args = get_args(argc, argv);
	mise_en_place(&dinner);
	call_philos_to_dinner(&dinner);
	start_dinner(&dinner);
	finish_dinner(&dinner);
	return (0);
}
