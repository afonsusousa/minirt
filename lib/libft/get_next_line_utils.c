/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:28:33 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 18:45:58 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_newlen(const char *str)
{
	char	*start;

	start = (char *)str;
	if (!str)
		return (0);
	while (*str && *str != '\n')
		str++;
	return (str - start + (*str == '\n'));
}
