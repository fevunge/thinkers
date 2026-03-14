/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:33:18 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/14 14:36:04 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define ARGUMENT_ERROR 010
# define MEMORY_ERROR 020
# define THREAD_ERROR 030
# define UKNOW_ERROR 040
# define TRUE 1
# define FALSE 0
# define SIGNAL_PLUS '+'
# define SIGNAL_MINUS '-'
# define TAKE_FORK_LOG "has taken a fork"
# define EAT_LOG "is eating"
# define SLEEP_LOG "is sleeping"
# define THINK_LOG "is thinking"
# define DEATH_LOG "died"
# define ARG_TYPE_ERROR_MSG "Arguments must been positive integer\n"
# define ARG_LEN_ERROR_MSG "Program must take between 4 or 5 arguments\n"

# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>

typedef unsigned int	t_bool;
typedef unsigned int	t_natural;
typedef unsigned char	t_signal;
typedef unsigned long	t_milisecond;

typedef struct s_args
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
}	t_args;

typedef struct s_resource
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}	t_resource;

typedef struct s_waiter
{
	pthread_t	thread_id;
}	t_waiter;

typedef struct s_philo
{
	t_natural		id;
	pthread_t		thread_id;
	t_resource		resources;
	t_milisecond	die;
	t_milisecond	eat;
	t_milisecond	sleep;
	t_milisecond	last_meal;
	int				must_eat;
	int				eaten;
	t_milisecond	born_at;
}	t_philo;

typedef struct s_dinner
{
	t_philo			*philos;
	t_waiter		*waiter;
	t_args			args;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*forks;
}	t_dinner;

void			*waiter_work(void *arg);
void			mise_en_place(t_dinner *dinner);
void			call_philos_to_dinner(t_dinner *dinner);
void			*philo_start_launch(void *arg);
void			philo_launch(t_philo *philo);
void			start_dinner(t_dinner *dinner);
void			finish_dinner(t_dinner *dinner);
t_bool			philo_starved(t_philo philo);
t_waiter		*call_waiter(t_dinner *dinner);

// IO
void			get_error(int error, const char *message);
void			get_log(t_philo *philo, const char *log_message);
t_args			get_args(int argc, const char *argv[]);

// utils

long			ft_atoi(const char *str);
void			ft_usleep(t_milisecond mls);
t_bool			ft_s_is_digit(const char *message);
size_t			ft_strlen(const char *str);
t_milisecond	ft_time_now(void);

#endif