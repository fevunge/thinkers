/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:54:27 by fevunge           #+#    #+#             */
/*   Updated: 2026/03/09 14:51:17 by fevunge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# define TRUE 1
# define TRUE 1
# define SIGNAL_PLUS '+'
# define SIGNAL_MINUS '-'
# include <sys/types.h>

typedef unsigned int	t_bool;
typedef unsigned char	t_signal;

size_t	string_len(const char *str);
int		string_to_int(const char *str);
#endif