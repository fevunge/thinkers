#include "thinker.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}
