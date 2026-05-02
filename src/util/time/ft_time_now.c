#include "thinker.h"

t_milisecond	ft_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		get_error(UKNOW_ERROR, "Error getting time from gettimeofday() func\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
