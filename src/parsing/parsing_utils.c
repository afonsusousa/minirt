/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:47 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:54:21 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

size_t	magnitude(char *n)
{
	size_t	mag;

	if (!n || !*n)
		return (1);
	if (*n == '+' || *n == '-')
		n++;
	mag = 0;
	while (ft_isdigit(*n++))
		mag++;
	return (mag);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	skip(char **s, bool (*predicate)(char))
{
	bool	ret;

	ret = false;
	while (**s && predicate(**s))
	{
		(*s)++;
		ret = true;
	}
	return (ret);
}

bool	match_id(char **line, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(*line, id, len) == 0)
	{
		*line += len;
		return (true);
	}
	return (false);
}
