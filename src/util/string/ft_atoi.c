#include "thinker.h"

static t_bool	is_space(char c)
{
	if (c == 32)
		return (1);
	return (c <= 13 && c >= 9);
}

static t_bool	is_signal(char c)
{
	return (c == SIGNAL_PLUS || c == SIGNAL_MINUS);
}

static t_bool	is_digit(char c)
{
	return (c <= '9' && c >= '0');
}

long	ft_atoi(const char *str)
{
	long		number;
	int			sign;

	sign = 1;
	number = 0;
	if (!str)
		return (number);
	while (is_space(*str))
		str++;
	if (is_signal(*str))
	{
		if (*str == SIGNAL_MINUS)
			sign = -1;
		str++;
	}
	while (is_digit(*str))
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return ((int)(sign * number));
}
