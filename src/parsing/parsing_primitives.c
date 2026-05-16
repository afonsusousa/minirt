/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_primitives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:51 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 21:31:23 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../lib/libft/libft.h"
#include "parsing.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

t_parse_status	parse_double(char **line, double *d)
{
	double	integer;
	double	decimal;
	char	*dstart;

	if (!ft_isdigit(**line) && **line != '-' && **line != '+')
		return (PARSE_SYNTAX_ERROR);
	integer = ft_atoi((const char *)*line);
	*line += magnitude(*line) + (integer < 0 || **line == '+' || **line == '-');
	if (**line != '.')
	{
		*d = (double)integer;
		return (PARSE_OK);
	}
	(*line)++;
	if (!ft_isdigit(**line))
		return (PARSE_SYNTAX_ERROR);
	dstart = *line;
	decimal = ft_atoi((const char *)*line);
	*d = (double)integer + (((integer < 0) * -1) + (integer >= 0)) * (decimal
			/ pow(10.0, (double)magnitude(dstart)));
	*line += magnitude(dstart);
	return (PARSE_OK);
}

t_parse_status	parse_vec3_uchar(char **line, t_vec3 *vec)
{
	unsigned char	x;
	unsigned char	y;
	unsigned char	z;

	if (!ft_isdigit(**line))
		return (PARSE_SYNTAX_ERROR);
	x = ft_atoi((const char *)*line);
	*line += magnitude(*line);
	if (**line != ',')
		return (PARSE_SYNTAX_ERROR);
	(*line)++;
	if (!ft_isdigit(**line))
		return (PARSE_SYNTAX_ERROR);
	y = ft_atoi((const char *)*line);
	*line += magnitude(*line);
	if (**line != ',')
		return (PARSE_SYNTAX_ERROR);
	(*line)++;
	if (!ft_isdigit(**line))
		return (PARSE_SYNTAX_ERROR);
	z = ft_atoi((const char *)*line);
	*line += magnitude(*line);
	*vec = vec3(x / 255.0, y / 255.0, z / 255.0);
	return (PARSE_OK);
}

t_parse_status	parse_vec3_double(char **line, t_vec3 *vec)
{
	double			x;
	double			y;
	double			z;
	t_parse_status	status;

	status = parse_double(line, &x);
	if (status != PARSE_OK)
		return (status);
	if (**line != ',')
		return (PARSE_SYNTAX_ERROR);
	(*line)++;
	status = parse_double(line, &y);
	if (status != PARSE_OK)
		return (status);
	if (**line != ',')
		return (PARSE_SYNTAX_ERROR);
	(*line)++;
	status = parse_double(line, &z);
	if (status != PARSE_OK)
		return (status);
	*vec = vec3(x, y, z);
	return (PARSE_OK);
}

t_parse_status	parse_nvec3_double(char **line, t_vec3 *vec)
{
	t_vec3			tmp;
	t_parse_status	status;

	status = parse_vec3_double(line, &tmp);
	if (status != PARSE_OK)
		return (status);
	if (v3_len(tmp) > 1.0)
		return (PARSE_NOT_NORMALIZED);
	*vec = v3_unit(tmp);
	return (PARSE_OK);
}
