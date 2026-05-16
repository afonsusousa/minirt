/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:32 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:10:57 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/intersection.h"
#include "../includes/render.h"
#include "intersection.h"
#include "obj.h"
#include "ray.h"
#include "stdbool.h"
#include "vec3.h"
#include <math.h>

void	set_face_normal(t_hit *record, t_ray *ray,
		t_vec3 outward_normal)
{
	record->front_face = v3_dot(&ray->direction, &outward_normal) < 0.0;
	if (record->front_face)
		record->n = outward_normal;
	else
		record->n = v3_neg(outward_normal);
}

t_vec3	ray_at(t_ray *ray, double t)
{
	t_vec3	mult;

	mult = v3_muls(ray->direction, t);
	return (v3_add(ray->origin, mult));
}

bool	hit(t_obj *obj, t_hit_ctx *ctx)
{
	if (obj->type == OBJ_SPHERE)
		return (hit_sphere(obj, ctx));
	if (obj->type == OBJ_CYLINDER)
		return (hit_cylinder(obj, ctx));
	if (obj->type == OBJ_PLANE)
		return (hit_plane(obj, ctx));
	return (false);
}

bool	get_closest_hit(t_ray *r, t_world *w, t_hit *rec, t_vec3 *color)
{
	t_hit_ctx	ctx;
	bool		hit_any;
	double		closest;
	size_t		i;
	size_t		closest_idx;

	hit_any = false;
	closest = INFINITY;
	closest_idx = 0;
	i = 0;
	while (i < w->num_objects)
	{
		ctx = (t_hit_ctx){r, (t_interval){0.005, closest}, rec};
		if (hit(&w->objects[i], &ctx))
		{
			hit_any = true;
			closest = rec->t;
			closest_idx = i;
		}
		i++;
	}
	if (hit_any)
		*color = w->objects[closest_idx].color;
	return (hit_any);
}
