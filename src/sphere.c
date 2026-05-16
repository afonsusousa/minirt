/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:07 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:54:41 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/intersection.h"
#include "../includes/obj.h"
#include "../includes/ray.h"
#include "../includes/vec3.h"
#include <stdbool.h>
#include <stdlib.h>

static bool	find_sphere_root(t_quad_calc *calc, t_hit_ctx *ctx, double sqrt_d);

bool	hit_sphere(t_obj *sphere, t_hit_ctx *ctx)
{
	t_quad_calc	calc;
	double		sqrt_d;
	t_vec3		outward_normal;

	calc.oc = v3_sub(sphere->shape.sphere.center, ctx->ray->origin);
	calc.a = v3_dot(&ctx->ray->direction, &ctx->ray->direction);
	calc.half_b = v3_dot(&ctx->ray->direction, &calc.oc);
	calc.c = v3_dot(&calc.oc, &calc.oc) - sphere->shape.sphere.radius
		* sphere->shape.sphere.radius;
	calc.d = calc.half_b * calc.half_b - calc.a * calc.c;
	if (calc.d < 0)
		return (false);
	sqrt_d = sqrt(calc.d);
	if (!find_sphere_root(&calc, ctx, sqrt_d))
		return (false);
	ctx->record->t = calc.root;
	ctx->record->p = ray_at(ctx->ray, ctx->record->t);
	outward_normal = v3_divs(v3_sub(ctx->record->p,
				sphere->shape.sphere.center), sphere->shape.sphere.radius);
	set_face_normal(ctx->record, ctx->ray, v3_unit(outward_normal));
	return (true);
}

static bool	find_sphere_root(t_quad_calc *calc, t_hit_ctx *ctx, double sqrt_d)
{
	calc->root = (calc->half_b - sqrt_d) / calc->a;
	if (surrounds(ctx->ray_t, calc->root))
		return (true);
	calc->root = (calc->half_b + sqrt_d) / calc->a;
	if (surrounds(ctx->ray_t, calc->root))
		return (true);
	return (false);
}
