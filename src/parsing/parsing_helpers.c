/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:59:26 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 21:22:38 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/obj.h"
#include "../../includes/world.h"
#include "parsing.h"

t_parse_status	parse_ambient(char **line, t_world *wrld)
{
	t_parse_status	status;

	if (wrld->has_ambient)
		return (PARSE_SYNTAX_ERROR);
	status = parse_format(wrld, &wrld->ambient, get_ambient_fmt(), line);
	if (status != PARSE_OK)
		return (status);
	wrld->has_ambient = true;
	return (PARSE_OK);
}

t_parse_status	parse_camera(char **line, t_world *wrld)
{
	t_parse_status	status;

	if (wrld->has_camera)
		return (PARSE_SYNTAX_ERROR);
	status = parse_format(wrld, &wrld->camera, get_camera_fmt(), line);
	if (status != PARSE_OK)
		return (status);
	wrld->has_camera = true;
	return (PARSE_OK);
}

t_parse_status	parse_light(char **line, t_world *wrld)
{
	void	*target;

	target = &wrld->lights[wrld->num_lights++];
	return (parse_format(wrld, target, get_light_fmt(), line));
}

t_parse_status	parse_color_field(t_world *wrld, void *target,
		const t_format *fmt, char **line)
{
	void	*field;

	(void)wrld;
	field = (char *)target + fmt->offset;
	if (!skip(line, ft_isspace))
		return (PARSE_SYNTAX_ERROR);
	return (parse_vec3_uchar(line, (t_vec3 *)field));
}
