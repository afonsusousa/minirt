/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:27:51 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:27:52 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vec3.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = 0.0;
	return (res);
}

t_vec3	v3_add(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	v3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	v3_mul(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	v3_sq(t_vec3 a)
{
	return (v3_mul(a, a));
}
