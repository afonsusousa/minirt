/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_primitives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:51 by amagno-r          #+#    #+#             */
/*   Updated: 2026/04/25 18:56:52 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../lib/libft/libft.h"
#include <math.h>
#include "vec3.h"
#include <stdbool.h>

bool  parse_double(char **line, double *d)
{
    double integer;
    double decimal;

    if (!ft_isdigit(**line) && **line != '-' && **line != '+')
        return (false);
    integer = ft_atoi((const char *)*line);
    *line += magnitude(integer) + (integer < 0 || **line == '+' || **line == '-');
    if (**line != '.')
    {
        *d = (double)integer;
        return (true);
    }
    (*line)++;
    if (!ft_isdigit(**line))
        return (false);
    decimal = ft_atoi((const char *) *line);
    *d = (double) integer 
        + (((integer < 0) * -1) + (integer >= 0)) 
        * (decimal / pow(10.0, (double) magnitude(decimal)));
    *line += magnitude(decimal);
    return (true);
}

//maybe move the division upstream
bool    parse_vec3_uchar(char **line, t_vec3    *vec)
{
    unsigned char x;
    unsigned char y;
    unsigned char z;

    if (!ft_isdigit(**line))
        return (false);
    x = ft_atoi((const char *)*line);
    *line += magnitude(x);
    if (**line != ',')
        return (false);
    (*line)++;
    if (!ft_isdigit(**line))
        return (false);
    y = ft_atoi((const char *)*line);
    *line += magnitude(y);
    if (**line != ',')
        return (false);
    (*line)++;
    if (!ft_isdigit(**line))
        return (false);
    z = ft_atoi((const char *)*line);
    *line += magnitude(z);
    *vec = vec3(x / 255.0, y / 255.0, z / 255.0);
    return (true);
}

bool    parse_vec3_double(char **line, t_vec3   *vec)
{
    double  x;
    double  y;
    double  z;

    if (!parse_double(line, &x) || **line != ',')
        return (false);
    (*line)++;
    if (!parse_double(line, &y) || **line != ',')
        return (false);
    (*line)++;
    if (!parse_double(line, &z))
        return (false);
    *vec = vec3(x, y, z);
    return (true);
}