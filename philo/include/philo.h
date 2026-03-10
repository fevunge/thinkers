/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:33:18 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/10 03:53:16 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define ARGUMENT_ERROR 011
# define MEMORY_ERROR 021
# define THREAD_ERROR 031;
# define TRUE 1
# define FALSE 0
# define SIGNAL_PLUS '+'
# define SIGNAL_MINUS '-'
# define DEV "fevunge"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>

typedef unsigned int t_bool;
typedef unsigned int t_natural;
typedef unsigned char t_signal;
typedef unsigned long t_milisecond;

typedef struct s_args
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int times_must_eat;
} t_args;

typedef struct s_resource
{
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *write_lock;
	pthread_mutex_t *meal_lock;
} t_resource;

typedef struct s_philo
{
	t_natural id;
	pthread_t thread_id;
	t_resource resources;
	t_milisecond die;
	t_milisecond eat;
	t_milisecond sleep;
	t_milisecond last_meal;
	t_milisecond born_at;
} t_philo;

typedef struct s_dinner
{
	t_philo *philos;
	t_args args;
	t_resource *meal_lock;
	t_resource *write_lock;
	pthread_mutex_t *both_forks;
} t_dinner;


void call_philos_to_dinner(t_philo *philos, t_dinner *dinner);
void start_dinner(t_dinner *dinner);
void finish_dinner(t_dinner *dinner);

//IO
void	get_error(int error, const char *message);
t_args	get_args(int argc, const char *argv[]);

// utils
t_bool ft_s_is_digit(const char *message);
size_t ft_strlen(const char *str);
int ft_atoi(const char *str);

#endif