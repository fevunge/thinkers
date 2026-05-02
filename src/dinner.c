#include "thinker.h"

static void	provide_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.philos_n)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL) != 0)
			finish_dinner(dinner);
		i++;
	}
}

static void	start_philos(t_dinner *dinner)
{
	int				i;
	t_milisecond	start;

	i = 0;
	start = ft_time_now();
	while (i < dinner->args.philos_n)
	{
		dinner->philos[i].born_at = start;
		dinner->philos[i].last_meal = start;
		i++;
	}
}

void	mise_en_place(t_dinner *dinner)
{
	dinner->forks = ft_salloc(sizeof(pthread_mutex_t), dinner->args.philos_n);
	dinner->philos = ft_salloc(sizeof(t_thinker), dinner->args.philos_n);
	dinner->write_lock = ft_salloc(sizeof(pthread_mutex_t), 1);
	dinner->meal_lock = ft_salloc(sizeof(pthread_mutex_t), 1);
	dinner->death_lock = ft_salloc(sizeof(pthread_mutex_t), 1);
	dinner->start_lock = ft_salloc(sizeof(pthread_mutex_t), 1);
	if (pthread_mutex_init(dinner->write_lock, NULL) != 0)
		finish_dinner(dinner);
	if (pthread_mutex_init(dinner->meal_lock, NULL) != 0)
		finish_dinner(dinner);
	if (pthread_mutex_init(dinner->death_lock, NULL) != 0)
		finish_dinner(dinner);
	if (pthread_mutex_init(dinner->start_lock, NULL) != 0)
		finish_dinner(dinner);
	provide_forks(dinner);
	return ;
}

void	start_dinner(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->somebody_die = FALSE;
	dinner->start_simulation = FALSE;
	start_philos(dinner);
	while (i < dinner->args.philos_n)
	{
		if (pthread_create(&dinner->philos[i].thread_id,
				NULL, &philo_start_launch, &dinner->philos[i]) != 0)
			finish_dinner(dinner);
		i++;
	}
	call_waiter(dinner);
	pthread_mutex_lock(dinner->start_lock);
	dinner->start_simulation = TRUE;
	pthread_mutex_unlock(dinner->start_lock);
	i = 0;
	while (i < dinner->args.philos_n)
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
	while (i < dinner->args.philos_n)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		i++;
	}
	free(dinner->forks);
	free(dinner->philos);
	pthread_mutex_destroy(dinner->write_lock);
	pthread_mutex_destroy(dinner->meal_lock);
	pthread_mutex_destroy(dinner->death_lock);
	pthread_mutex_destroy(dinner->start_lock);
	free(dinner->write_lock);
	free(dinner->meal_lock);
	free(dinner->death_lock);
	free(dinner->start_lock);
	return ;
}
