/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:32 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/13 15:01:31 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "intersection.h"
#include "../includes/intersection.h"
#include "obj.h"
#include "ray.h"
#include "stdbool.h"
#include <math.h>
#include "../includes/render.h"

bool hit(t_obj *obj, t_hit_ctx *ctx)
{
	switch (obj->type)
	{
		case OBJ_SPHERE:
			return (hit_sphere(obj, ctx));
		case OBJ_CYLINDER:
			return (hit_cylinder(obj, ctx));
		case OBJ_PLANE:
			return (hit_plane(obj, ctx));
		default:
			return (false);
	}
}

bool	get_closest_hit(t_ray *r, t_world *w, t_hit *rec, t_material **mat)
{
	t_hit_ctx	ctx;
	bool		hit_any;
	double		closest;
	size_t		i;

	hit_any = false;
	closest = INFINITY;
	i = 0;
	while (i < w->num_objects)
	{
		ctx = (t_hit_ctx){r, (t_interval){0.005, closest}, rec};
		if (hit(&w->objects[i], &ctx))
		{
			hit_any = true;
			closest = rec->t;
			*mat = &w->materials[w->objects[i].mat_idx];
		}
		i++;
	}
	return (hit_any);
}
