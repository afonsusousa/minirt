/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by afonsusousa       #+#    #+#             */
/*   Updated: 2026/05/16 21:25:58 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_parse_status	parse_ambient(char **line, t_world *wrld);
t_parse_status	parse_camera(char **line, t_world *wrld);
t_parse_status	parse_light(char **line, t_world *wrld);

static bool	match_object(char **line, t_world *wrld, void **target,
		const t_format **fmt)
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

static t_parse_status	parse_format_field(void *field,
		const t_format *fmt, char **line)
{
	if (fmt->type == F_VEC3)
	{
		if (!skip(line, ft_isspace))
			return (PARSE_SYNTAX_ERROR);
		return (parse_vec3_double(line, field));
	}
	if (fmt->type == F_NVEC3)
	{
		if (!skip(line, ft_isspace))
			return (PARSE_SYNTAX_ERROR);
		return (parse_nvec3_double(line, field));
	}
	if (fmt->type == F_DOUBLE)
	{
		if (!skip(line, ft_isspace))
			return (PARSE_SYNTAX_ERROR);
		return (parse_double(line, field));
	}
	if (fmt->type == F_COLOR)
	{
		if (!skip(line, ft_isspace))
			return (PARSE_SYNTAX_ERROR);
		return (parse_vec3_uchar(line, field));
	}
	return (PARSE_SYNTAX_ERROR);
}

t_parse_status	parse_format(void *target, const t_format *fmt,
		char **line)
{
	int				i;
	t_parse_status	status;

	i = -1;
	while (fmt[++i].type != F_END)
	{
		status = parse_format_field((char *)target + fmt[i].offset, &fmt[i],
				line);
		if (status != PARSE_OK)
			return (status);
	}
	return (PARSE_OK);
}

t_parse_status	parse_line(char **line, t_world *wrld)
{
	void			*target;
	const t_format	*fmt;

	skip(line, ft_isspace);
	if (**line == '\0' || **line == '\n')
		return (PARSE_OK);
	if (match_object(line, wrld, &target, &fmt))
		return (parse_format(target, fmt, line));
	if (match_id(line, "A"))
		return (parse_ambient(line, wrld));
	if (match_id(line, "C"))
		return (parse_camera(line, wrld));
	if (match_id(line, "L"))
		return (parse_light(line, wrld));
	return (PARSE_SYNTAX_ERROR);
}
