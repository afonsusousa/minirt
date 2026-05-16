/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:59:26 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 21:01:43 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/obj.h"
#include "../../includes/world.h"
#include "parsing.h"

bool	parse_ambient(char **line, t_world *wrld)
{
	if (wrld->has_ambient)
		return (false);
	if (!parse_format(wrld, &wrld->ambient, get_ambient_fmt(), line))
		return (false);
	wrld->has_ambient = true;
	return (true);
}

bool	parse_camera(char **line, t_world *wrld)
{
	if (wrld->has_camera)
		return (false);
	if (!parse_format(wrld, &wrld->camera, get_camera_fmt(), line))
		return (false);
	wrld->has_camera = true;
	return (true);
}

bool	parse_light(char **line, t_world *wrld)
{
	void	*target;

	target = &wrld->lights[wrld->num_lights++];
	return (parse_format(wrld, target, get_light_fmt(), line));
}

bool	parse_color_field(t_world *wrld, void *target, const t_format *fmt,
		char **line)
{
	void	*field;

	(void)wrld;
	field = (char *)target + fmt->offset;
	if (!skip(line, ft_isspace))
		return (false);
	if (!parse_vec3_uchar(line, (t_vec3 *)field))
		return (false);
	return (true);
}
