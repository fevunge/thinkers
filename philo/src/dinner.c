/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:10:02 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/15 20:50:48 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	provide_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.number_of_philos)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL) != 0)
			finish_dinner(dinner);
		i++;
	}
}

void	mise_en_place(t_dinner *dinner)
{
	size_t	fork_quantity;
	
	fork_quantity = dinner->args.number_of_philos;
	dinner->forks = ft_salloc(sizeof(pthread_mutex_t), fork_quantity);
	dinner->philos = ft_salloc(sizeof(t_philo), fork_quantity);
	
	dinner->write_lock = ft_salloc(sizeof(pthread_mutex_t), 1);
	dinner->meal_lock = ft_salloc(sizeof(pthread_mutex_t), 1);
	dinner->dead_lock = ft_salloc(sizeof(pthread_mutex_t), 1);
	if (pthread_mutex_init(dinner->write_lock, NULL) != 0)
		finish_dinner(dinner);
	if (pthread_mutex_init(dinner->meal_lock, NULL) != 0)
		finish_dinner(dinner);
	if (pthread_mutex_init(dinner->dead_lock, NULL) != 0)
		finish_dinner(dinner);
	provide_forks(dinner);
	return ;
}

void	start_dinner(t_dinner *dinner)
{
	int				i;
	t_milisecond	start;

	i = 0;
	start = ft_time_now();
	dinner->somebody_die = FALSE;
	while (i < dinner->args.number_of_philos)
	{
		dinner->philos[i].born_at = start;
		dinner->philos[i].last_meal = start;
		i++;
	}
	call_waiter(dinner);
	i = 0;
	while (i < dinner->args.number_of_philos)
	{
		if (pthread_create(&dinner->philos[i].thread_id,
				NULL, &philo_start_launch, &dinner->philos[i]) != 0)
			finish_dinner(dinner);
		i++;
	}
	i = 0;
	while (i < dinner->args.number_of_philos)
	{
		if (pthread_join(dinner->philos[i].thread_id, NULL) != 0)
			finish_dinner(dinner);
		i++;
	}
	if (pthread_join(dinner->waiter, NULL) != 0)
		finish_dinner(dinner);
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
	free(dinner->forks);
	free(dinner->philos);
	pthread_mutex_destroy(dinner->write_lock);
	pthread_mutex_destroy(dinner->meal_lock);
	pthread_mutex_destroy(dinner->dead_lock);
	free(dinner->write_lock);
	free(dinner->meal_lock);
	free(dinner->dead_lock);
	return ;
}
