/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:27:46 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:27:46 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vec3.h"
#include <math.h>

double	v3_len(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	v3_unit(t_vec3 vec)
{
	double	len;

	len = sqrt(v3_len_sq(vec));
	return (vec3(vec.x / len, vec.y / len, vec.z / len));
}

void	v3_unit_mut(t_vec3 *dest)
{
	double	length;

	length = sqrt(dest->x * dest->x + dest->y * dest->y + dest->z * dest->z);
	dest->x /= length;
	dest->y /= length;
	dest->z /= length;
	dest->w = 0.0;
}

int	v3_near_zero(t_vec3 vec)
{
	double	s;

	s = 1e-8;
	return (fabs(vec.x) < s && fabs(vec.y) < s && fabs(vec.z) < s);
}
