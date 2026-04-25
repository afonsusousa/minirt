/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:38 by amagno-r          #+#    #+#             */
/*   Updated: 2026/04/25 18:56:39 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include <stdbool.h>
# include "../includes/obj.h"

// parsing_utils.c
size_t	magnitude(int n);
bool	ft_isspace(char c);
bool	skip(char **s, bool (*predicate)(char));
bool	match_id(char **line, char *id);
char	*get_next_line(int fd);

// parsing_error.c
void	syntax_error(const char *file, int line, const char *start, const char *c);

bool	parse_double(char **line, double *d);
bool	parse_vec3_double(char **line, t_vec3 *vec);
bool	parse_vec3_uchar(char **line, t_vec3 *vec);

bool    parse_line(char **line, t_world *wrld);

const t_format  *get_sphere_fmt(void);
const t_format  *get_plane_fmt(void);
const t_format  *get_cylinder_fmt(void);
const t_format  *get_ambient_fmt(void);
const t_format  *get_camera_fmt(void);
const t_format  *get_light_fmt(void);

#endif