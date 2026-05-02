#include "thinker.h"

void	ft_usleep(t_milisecond mls)
{
	t_milisecond	start;

	start = ft_time_now();
	while (ft_time_now() - start < mls)
		usleep(500);
}
