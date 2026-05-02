#include "thinker.h"

void	get_log(t_thinker *thinker, const char *log_message)
{
	t_milisecond	age;

	pthread_mutex_lock(thinker->death_lock);
	if (*thinker->somebody_die)
	{
		pthread_mutex_unlock(thinker->death_lock);
		return ;
	}
	pthread_mutex_lock(thinker->write_lock);
	age = ft_time_now() - thinker->born_at;
	printf("%ld %d %s\n", age, thinker->id, log_message);
	pthread_mutex_unlock(thinker->write_lock);
	pthread_mutex_unlock(thinker->death_lock);
	return ;
}
