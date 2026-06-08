/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:23:35 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/22 18:04:49 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/intersection.h"
#include "../includes/interval.h"
#include "../includes/obj.h"
#include "../includes/vec3.h"

void	setup_quad(t_obj *cylinder, t_hit_ctx *ctx, t_quad_calc *calc)
{
	double	axis_dot_dir;
	double	axis_dot_oc;

	axis_dot_dir = v3_dot(&ctx->ray->direction,
			&cylinder->u_shape.s_cylinder.dir);
	axis_dot_oc = v3_dot(&calc->oc,
			&cylinder->u_shape.s_cylinder.dir);
	calc->a = v3_dot(&ctx->ray->direction, &ctx->ray->direction) - axis_dot_dir
		* axis_dot_dir;
	calc->half_b = v3_dot(&ctx->ray->direction, &calc->oc) - (axis_dot_dir
			* axis_dot_oc);
	calc->c = v3_dot(&calc->oc, &calc->oc) - axis_dot_oc * axis_dot_oc
		- (cylinder->u_shape.s_cylinder.diameter / 2.0)
		* (cylinder->u_shape.s_cylinder.diameter / 2.0);
}

bool	check_cylinder_root(t_obj *cylinder, t_hit_ctx *ctx, double root)
{
	double	proj;
	t_vec3	p_minus_c;
	t_vec3	p;

	if (!surrounds(ctx->ray_t, root))
		return (false);
	p = ray_at(ctx->ray, root);
	p_minus_c = v3_sub(p, cylinder->u_shape.s_cylinder.pos);
	proj = v3_dot(&p_minus_c, &cylinder->u_shape.s_cylinder.dir);
	if (fabs(proj) <= cylinder->u_shape.s_cylinder.height / 2.0)
	{
		ctx->record->t = root;
		ctx->record->p = p;
		return (true);
	}
	return (false);
}
