/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_components.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/22 18:09:28 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"
#include <math.h>

t_vec3	calc_ambient(t_phong_ctx *ctx)
{
	return (v3_mul(v3_muls(ctx->world->ambient.color,
				ctx->world->ambient.ratio), ctx->obj_color));
}

t_vec3	calc_diffuse(t_phong_ctx *ctx, t_vec3 l_dir, size_t idx)
{
	double	n_dot_l;

	n_dot_l = fmax(0.0, v3_dot(&ctx->record->n, &l_dir));
	return (v3_muls(v3_mul(ctx->obj_color, ctx->world->lights[idx].color),
			ctx->world->lights[idx].ratio * DIFFUSE_INTENSITY * n_dot_l));
}

t_vec3	calc_specular(t_phong_ctx *ctx, t_vec3 l_dir, size_t idx)
{
	t_vec3	r_dir;
	t_vec3	v_dir;
	double	spec;

	v_dir = v3_unit(v3_sub(ctx->ray->origin, ctx->record->p));
	r_dir = v3_reflect(v3_neg(l_dir), ctx->record->n);
	spec = pow(fmax(0.0, v3_dot(&v_dir, &r_dir)), SHININESS);
	return (v3_muls(ctx->world->lights[idx].color,
			ctx->world->lights[idx].ratio * SPEC_INTENSITY * spec));
}
