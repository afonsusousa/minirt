/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@local>                      +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:00:00 by automated         #+#    #+#             */
/*   Updated: 2026/05/16 20:00:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vec3.h"

t_vec3	v3_muls(t_vec3 vec, double t)
{
	return (vec3(t * vec.x, t * vec.y, t * vec.z));
}

t_vec3	v3_smul(double t, t_vec3 vec)
{
	return (v3_muls(vec, t));
}

t_vec3	v3_divs(t_vec3 vec, double t)
{
	return (vec3(vec.x / t, vec.y / t, vec.z / t));
}

t_vec3	v3_neg(t_vec3 vec)
{
	return (vec3(-vec.x, -vec.y, -vec.z));
}

t_vec3	v3_reflect(t_vec3 v, t_vec3 n)
{
	t_vec3	scaled_n;

	scaled_n = v3_muls(n, 2.0 * (v.x * n.x + v.y * n.y + v.z * n.z));
	return (v3_sub(v, scaled_n));
}
