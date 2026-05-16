/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by afonsusousa       #+#    #+#             */
/*   Updated: 2026/05/16 19:25:24 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "unistd.h"
#include "fcntl.h"
#include <math.h>
#include "../../includes/obj.h"
#include "../../includes/world.h"
#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

static bool	parse_color_field(t_world *wrld, void *target,
		const t_format *fmt, char **line)
{
	void	*field;

	(void)	wrld;
	field = (char *)target + fmt->offset;
	if (!skip(line, ft_isspace))
		return (false);
	if (!parse_vec3_uchar(line, (t_vec3 *)field))
		return (false);
	return (true);
}

static bool	parse_format_field(t_world *wrld, void *target,
			const t_format *fmt, char **line)
{
	void	*field;

	field = (char *)target + fmt->offset;
	if (fmt->type == F_VEC3)
		return (skip(line, ft_isspace) && \
			parse_vec3_double(line, field));
	else if (fmt->type == F_NVEC3)
		return (skip(line, ft_isspace) && \
			parse_nvec3_double(line, field));
	else if (fmt->type == F_DOUBLE)
		return (skip(line, ft_isspace) && \
			parse_double(line, field));
	else if (fmt->type == F_COLOR)
		return (parse_color_field(wrld, target, fmt, line));
	return (false);
}

static bool	parse_format(t_world *wrld, void *target,
			const t_format *fmt, char **line)
{
	int	i;

	i = -1;
	while (fmt[++i].type != F_END)
	{
		if (!parse_format_field(wrld, target, &fmt[i], line))
			return (false);
	}
	return (true);
}

static bool	match_object(char **line, t_world *wrld,
				void **target, const t_format **fmt)
{
	*target = &wrld->objects[wrld->num_objects];
	if (match_id(line, "sp"))
	{
		((t_obj *)*target)->type = OBJ_SPHERE;
		*fmt = get_sphere_fmt();
	}
	else if (match_id(line, "pl"))
	{
		((t_obj *)*target)->type = OBJ_PLANE;
		*fmt = get_plane_fmt();
	}
	else if (match_id(line, "cy"))
	{
		((t_obj *)*target)->type = OBJ_CYLINDER;
		*fmt = get_cylinder_fmt();
	}
	else
		return (false);
	wrld->num_objects++;
	return (true);
}

bool	parse_line(char **line, t_world *wrld)
{
	void			*target;
	const t_format	*fmt;

	skip(line, ft_isspace);
	if (**line == '\0' || **line == '\n')
		return (true);
	if (match_object(line, wrld, &target, &fmt))
		return (parse_format(wrld, target, fmt, line));
	if (match_id(line, "A"))
		return (parse_format(wrld, &wrld->ambient, \
			get_ambient_fmt(), line));
	if (match_id(line, "C"))
		return (parse_format(wrld, &wrld->camera, \
			get_camera_fmt(), line));
	if (match_id(line, "L"))
	{
		target = &wrld->lights[wrld->num_lights++];
		return (parse_format(wrld, target, get_light_fmt(), line));
	}
	return (false);
}
