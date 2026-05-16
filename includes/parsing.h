/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:38 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 21:25:31 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../lib/libft/libft.h"
# include "world.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_parse_status
{
	PARSE_OK,
	PARSE_SYNTAX_ERROR,
	PARSE_NOT_NORMALIZED
}				t_parse_status;

size_t			magnitude(char *n);
bool			ft_isspace(char c);
bool			skip(char **s, bool (*predicate)(char));
bool			match_id(char **line, char *id);
void			syntax_error(const char *file, int line, const char *start,
					const char *c);
t_world			*parse_file(t_world *wrld, char *path);
t_parse_status		parse_double(char **line, double *d);
t_parse_status		parse_vec3_double(char **line, t_vec3 *vec);
t_parse_status		parse_nvec3_double(char **line, t_vec3 *vec);
t_parse_status		parse_vec3_uchar(char **line, t_vec3 *vec);
t_parse_status		parse_line(char **line, t_world *wrld);
t_parse_status		parse_format(t_world *wrld, void *target, const t_format *fmt,
							char **line);
const t_format	*get_sphere_fmt(void);
const t_format	*get_plane_fmt(void);
const t_format	*get_cylinder_fmt(void);
const t_format	*get_ambient_fmt(void);
const t_format	*get_camera_fmt(void);
const t_format	*get_light_fmt(void);
t_parse_status		parse_color_field(t_world *wrld, void *target, const t_format *fmt,
	char **line);

#endif