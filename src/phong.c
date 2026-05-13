/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:55:59 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/13 14:55:37 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"
#include "../includes/obj.h"
#include "../includes/camera.h"
#include "../includes/intersection.h"
#include "../includes/interval.h"
#include "../includes/world.h"
#include "../includes/render.h"
#include <math.h>

static bool	is_in_shadow(t_world *world, t_vec3 hit_p, t_vec3 l_dir, double d)
{
	t_ray		s_ray;
	t_hit		rec;
	t_hit_ctx	ctx;
	size_t		i;

	s_ray.origin = hit_p;
	s_ray.direction = l_dir;
	i = 0;
	while (i < world->num_objects)
	{
		ctx = (t_hit_ctx){&s_ray, (t_interval){0.01, d}, &rec};
		if (hit(&world->objects[i], &ctx))
			return (true);
		i++;
	}
	return (false);
}

static t_vec3	calc_direct_light(t_world *world, t_hit *record, t_ray *r, t_material *mat)
{
	t_phong_ctx	ctx;
	t_vec3		ambient;
	t_light		*light;
	size_t		i;

	ambient = v3_muls(world->ambient.color, world->ambient.ratio);
	ctx.tot = v3_mul(ambient, mat->color);
	ctx.v_dir = v3_unit(v3_muls(r->direction, -1.0));
	i = 0;
	while (i < world->num_lights)
	{
		light = &world->lights[i];
		ctx.l_dir = v3_sub(light->pos, record->p);
		ctx.dist = v3_len(ctx.l_dir);
		ctx.l_dir = v3_divs(ctx.l_dir, ctx.dist);
		if (!is_in_shadow(world, record->p, ctx.l_dir, ctx.dist))
		{
			// diffuse
			{
				double n_dot_l = fmax(0.0, v3_dot(&record->N, &ctx.l_dir));
				t_vec3 diff = v3_muls(v3_mul(mat->color, light->color), light->ratio * n_dot_l);
				ctx.tot = v3_add(ctx.tot, diff);
			}

			// specular
			ctx.ref_dir = v3_unit(v3_sub(v3_muls(record->N, 2.0 * v3_dot(&record->N, &ctx.l_dir)), ctx.l_dir));
			ctx.shininess = (mat->type == MAT_METAL) ? 128.0 : 32.0;
			ctx.specular_color = (mat->type == MAT_METAL) ? mat->color : vec3(1.0, 1.0, 1.0);
			{
				double r_dot_v = fmax(0.0, v3_dot(&ctx.ref_dir, &ctx.v_dir));
				double spec_fac = pow(r_dot_v, ctx.shininess);
				t_vec3 spec = v3_muls(v3_mul(light->color, ctx.specular_color), light->ratio * spec_fac);
				ctx.tot = v3_add(ctx.tot, spec);
			}
		}
		i++;
	}
	return (ctx.tot);
}

t_vec3	phong_ray_color(t_ray *r, t_world *w)
{
	t_hit		rec;
	t_material	*mat;
	t_vec3		direct;

	if (get_closest_hit(r, w, &rec, &mat))
	{
		direct = calc_direct_light(w, &rec, r, mat);
		return (direct);
	}
	return (v3_muls(w->ambient.color, w->ambient.ratio));
}
