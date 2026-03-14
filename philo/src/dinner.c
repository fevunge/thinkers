/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:10:02 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 14:29:51 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	provide_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.number_of_philos)
	{
		if (!pthread_mutex_init((&dinner->forks)[i], NULL))
			finish_dinner(dinner);
		i++;
	}
}

void	mise_en_place(t_dinner *dinner)
{
	size_t	fork_size;
	size_t	fork_quantity;

	fork_size = sizeof(pthread_mutex_t);
	fork_quantity = dinner->args.number_of_philos;
	dinner->forks = malloc(fork_size * fork_quantity);
	if (!dinner->forks)
		get_error(MEMORY_ERROR, "Error while allocating forks");
	dinner->philos = malloc(sizeof(t_philo) * fork_quantity);
	if (!dinner->philos)
		get_error(MEMORY_ERROR, "Error while allocating philos");
	if (!pthread_mutex_init(dinner->write_lock, NULL))
		finish_dinner(dinner);
	if (!pthread_mutex_init(dinner->meal_lock, NULL))
		finish_dinner(dinner);
	provide_forks(dinner);
	return ;
}

void	start_dinner(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->waiter = call_waiter(dinner);
	while (i < dinner->args.number_of_philos)
	{
		if (!pthread_create(&dinner->philos[i].thread_id,
				NULL, &philo_start_launch, &dinner->philos[i]))
			finish_dinner(dinner);
		i++;
	}
	if (!pthread_join(dinner->waiter->thread_id, NULL))
		finish_dinner(dinner);
	i = 0;
	while (i < dinner->args.number_of_philos)
	{
		if (!pthread_detach(dinner->philos[i].thread_id))
			finish_dinner(dinner);
		i++;
	}
	return ;
}

void	finish_dinner(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.number_of_philos)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		
		i++;
	}
	free(dinner->philos);
	free(dinner->forks);
	free(dinner->waiter);
	pthread_mutex_destroy(dinner->write_lock);
	pthread_mutex_destroy(dinner->meal_lock);
	
	return ;
}
