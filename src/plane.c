/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:28:05 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:28:06 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "interval.h"
#include "obj.h"
#include "vec3.h"
#include <math.h>

bool	hit_plane_math(t_hit_ctx *ctx, t_vec3 center, t_vec3 normal)
{
	t_plane_calc	calc;

	calc.denom = v3_dot(&ctx->ray->direction, &normal);
	if (fabs(calc.denom) < BASICALLY_ZERO)
		return (false);
	calc.oc = v3_sub(center, ctx->ray->origin);
	calc.t = v3_dot(&calc.oc, &normal) / calc.denom;
	if (!surrounds(ctx->ray_t, calc.t))
		return (false);
	ctx->record->t = calc.t;
	ctx->record->p = ray_at(ctx->ray, calc.t);
	set_face_normal(ctx->record, ctx->ray, normal);
	return (true);
}

bool	hit_plane(t_obj *plane, t_hit_ctx *ctx)
{
	return (hit_plane_math(ctx, plane->shape.plane.pos,
			plane->shape.plane.dir));
}
