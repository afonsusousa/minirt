/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:55:59 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:04:18 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"
#include "../includes/color.h"
#include "../includes/intersection.h"
#include "../includes/interval.h"
#include "../includes/obj.h"
#include "../includes/ray.h"
#include "../includes/render.h"
#include "../includes/vec3.h"
#include "../includes/world.h"
#include <math.h>

#define SHININESS 32.0
#define SPEC_INTENSITY 1.0
#define SHADOW_BIAS 0.01

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
		ctx = (t_hit_ctx){&s_ray, (t_interval){SHADOW_BIAS, d}, &rec};
		if (hit(&world->objects[i], &ctx))
			return (true);
		i++;
	}
	return (false);
}

static t_vec3	calc_ambient(t_phong_ctx ctx)
{
	return (v3_mul(v3_muls(ctx.world->ambient.color, ctx.world->ambient.ratio),
			ctx.obj_color));
}

static t_vec3	calc_diffuse(t_phong_ctx ctx, t_vec3 l_dir, size_t idx)
{
	double	n_dot_l;

	n_dot_l = fmax(0.0, v3_dot(&ctx.record->N, &l_dir));
	return (v3_muls(v3_mul(ctx.obj_color, ctx.world->lights[idx].color),
			ctx.world->lights[idx].ratio * n_dot_l));
}

static t_vec3	calc_specular(t_phong_ctx ctx, t_vec3 l_dir, size_t idx)
{
	t_vec3	h_dir;
	t_vec3	v_dir;
	double	spec;

	v_dir = v3_unit(v3_sub(ctx.ray->origin, ctx.record->p));
	h_dir = v3_unit(v3_add(l_dir, v_dir));
	spec = pow(fmax(0.0, v3_dot(&ctx.record->N, &h_dir)), SHININESS);
	return (v3_muls(ctx.world->lights[idx].color, ctx.world->lights[idx].ratio
			* SPEC_INTENSITY * spec));
}

static t_vec3	calc_direct_light(t_phong_ctx ctx)
{
	t_vec3	total;
	t_vec3	l_vec;
	t_vec3	l_dir;
	double	dist;
	size_t	i;

	total = calc_ambient(ctx);
	i = 0;
	while (i < ctx.world->num_lights)
	{
		l_vec = v3_sub(ctx.world->lights[i].pos, ctx.record->p);
		dist = v3_len(l_vec);
		l_dir = v3_unit(l_vec);
		if (!is_in_shadow(ctx.world, ctx.record->p, l_dir, dist))
		{
			if (v3_dot(&ctx.record->N, &l_dir) > 0.0)
			{
				total = v3_add(total, calc_diffuse(ctx, l_dir, i));
				total = v3_add(total, calc_specular(ctx, l_dir, i));
			}
		}
		i++;
	}
	return (total);
}

t_vec3	phong_ray_color(t_ray *r, t_world *w)
{
	t_hit		rec;
	t_vec3		color;
	t_phong_ctx	ctx;

	if (get_closest_hit(r, w, &rec, &color))
	{
		ctx = (t_phong_ctx){w, &rec, color, r};
		return (calc_direct_light(ctx));
	}
	return (v3_muls(w->ambient.color, w->ambient.ratio));
}
