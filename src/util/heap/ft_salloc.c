#include "thinker.h"

void	*ft_salloc(size_t size, size_t len)
{
	void	*mem;

	mem = malloc(size * len);
	if (!mem)
		get_error(MEMORY_ERROR, "Allocation error");
	return (mem);
}
