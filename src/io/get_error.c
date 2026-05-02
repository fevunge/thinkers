#include "thinker.h"

void	get_error(int error, const char *message)
{
	if (error == ARGUMENT_ERROR)
		write(2, "THE ARGUMENTS ARE NOT VALIDS\n", 29);
	if (error == MEMORY_ERROR)
		write(2, "MEMORY ALLOCATION ERROR\n", 25);
	if (error == THREAD_ERROR)
		write(2, "SOME THREAD ERROR\n", 18);
	write(2, message, ft_strlen(message));
	exit(1);
}
