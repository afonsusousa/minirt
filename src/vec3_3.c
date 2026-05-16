/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@local>                      +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:00:00 by automated         #+#    #+#             */
/*   Updated: 2026/05/16 20:00:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vec3.h"
#include <math.h>

double	v3_dot(const t_vec3 *a, const t_vec3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double	v3_len_sq(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3	v3_refract(t_vec3 v, t_vec3 n, double ri)
{
	t_vec3	neg_v;
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	neg_v = v3_neg(v);
	cos_theta = fmin(v3_dot(&neg_v, &n), 1.0);
	r_out_perp = v3_muls(v3_add(v, v3_muls(n, cos_theta)), ri);
	r_out_parallel = v3_muls(n, -sqrt(fabs(1.0 - v3_len_sq(r_out_perp))));
	return (v3_add(r_out_perp, r_out_parallel));
}

double	v3_reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	cosine = 1.0 - cosine;
	return (r0 + (1.0 - r0) * cosine * cosine * cosine * cosine * cosine);
}

t_vec3	v3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y
			* b.x));
}
