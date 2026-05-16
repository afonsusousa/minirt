/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:24:02 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:24:07 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/obj.h"
#include "../../includes/world.h"
#include "../../lib/libft/libft.h"
#include "fcntl.h"
#include "parsing.h"
#include "unistd.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	count_lines(char *path)
{
	int		fd;
	size_t	line_count;
	char	*line;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

static bool	alloc_world(t_world *wrld, size_t line_count)
{
	wrld->objects = ft_calloc(line_count, sizeof(t_obj));
	wrld->lights = ft_calloc(line_count, sizeof(t_light));
	if (!wrld->objects || !wrld->lights)
		return (false);
	wrld->num_objects = 0;
	wrld->num_lights = 0;
	wrld->has_camera = false;
	wrld->has_ambient = false;
	return (true);
}

static bool	parse_and_pack_lines(t_world *wrld, int fd, size_t count,
		char *path)
{
	size_t	i;
	char	*line;
	char	*curr;

	i = 0;
	while (i < count)
	{
		line = get_next_line(fd);
		curr = line;
		if (!parse_line(&curr, wrld))
		{
			syntax_error(path, i + 1, line, curr);
			free(line);
			return (false);
		}
		free(line);
		i++;
	}
	return (true);
}

t_world	*parse_file(t_world *wrld, char *path)
{
	int		fd;
	size_t	line_count;

	line_count = count_lines(path);
	if (!line_count || !alloc_world(wrld, line_count))
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!parse_and_pack_lines(wrld, fd, line_count, path))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (wrld);
}
