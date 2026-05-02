#include "thinker.h"

static int	get_argument(const char *arg)
{
	long	value;

	if (!ft_s_is_digit(arg))
		get_error(ARGUMENT_ERROR, ARG_TYPE_ERROR_MSG);
	value = ft_atoi(arg);
	if (value > INT_MAX || value <= 0)
		get_error(ARGUMENT_ERROR, ARG_TYPE_ERROR_MSG);
	return ((int)value);
}

t_args	get_args(int argc, const char *argv[])
{
	t_args	args;

	if (((argc - 1) / 2) != 2)
		get_error(ARGUMENT_ERROR, ARG_LEN_ERROR_MSG);
	args.philos_n = get_argument(argv[1]);
	args.time_to_die = get_argument(argv[2]);
	args.time_to_eat = get_argument(argv[3]);
	args.time_to_sleep = get_argument(argv[4]);
	if (argc == 6)
		args.times_must_eat = get_argument(argv[5]);
	else
		args.times_must_eat = -1;
	return (args);
}
