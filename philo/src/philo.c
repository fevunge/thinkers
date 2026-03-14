/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:29:48 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 14:34:06 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	call_philos_to_dinner(t_dinner *dinner)
{
	int	id;

	if (!dinner->philos)
		get_error(MEMORY_ERROR, "Philos not allocated");
	id = 0;
	while (id < dinner->args.number_of_philos)
	{
		dinner->philos[id].id = id + 1;
		dinner->philos[id].die = dinner->args.time_to_die;
		dinner->philos[id].eat = dinner->args.time_to_eat;
		dinner->philos[id].sleep = dinner->args.time_to_sleep;
		dinner->philos[id].must_eat = dinner->args.times_must_eat;
		dinner->philos[id].resources.left_fork = dinner->forks + id;
		dinner->philos[id].resources.right_fork = (void *)0;
		dinner->philos[id].resources.write_lock = dinner->write_lock;
		dinner->philos[id].resources.meal_lock = dinner->meal_lock;
		id++;
	}
	return ;
}

void	*philo_start_launch(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(philo->resources.meal_lock);
	philo->born_at = ft_time_now();
	philo->last_meal = ft_time_now();
	pthread_mutex_unlock(philo->resources.meal_lock);
	while (1)
		philo_launch(philo);
	return (NULL);
}

void	philo_launch(t_philo *philo)
{
	pthread_mutex_lock(philo->resources.left_fork);
	get_log(philo, TAKE_FORK_LOG);
	pthread_mutex_lock(philo->resources.right_fork);
	get_log(philo, TAKE_FORK_LOG);
	pthread_mutex_lock(philo->resources.meal_lock);
	get_log(philo, EAT_LOG);
	philo->eaten++;
	philo->last_meal = ft_time_now();
	pthread_mutex_unlock(philo->resources.meal_lock);
	ft_usleep(philo->eat);
	pthread_mutex_unlock(philo->resources.left_fork);
	pthread_mutex_unlock(philo->resources.right_fork);
	get_log(philo, SLEEP_LOG);
	ft_usleep(philo->sleep);
	get_log(philo, THINK_LOG);
}


t_bool	philo_starved(t_philo philo)
{
	t_milisecond	time_without_eat;

	time_without_eat = ft_time_now() - philo.last_meal;
	return (time_without_eat > philo.die);
}