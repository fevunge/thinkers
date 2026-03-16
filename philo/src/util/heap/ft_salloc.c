/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_salloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 11:49:13 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/15 11:57:23 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_salloc(size_t size, size_t len)
{
	void	*mem;
	mem = malloc(size * len);
	if (!mem)
		get_error(MEMORY_ERROR, "Allocation error");
	return (mem);
}