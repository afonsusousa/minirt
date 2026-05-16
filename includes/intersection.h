/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:29:35 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:29:37 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_INTERSECTION_H
# define MINIRT_INTERSECTION_H

# include "../includes/interval.h"
# include "obj.h"
# include "vec3.h"
# include <stdbool.h>

typedef struct s_hit
{
	t_vec3			p;
	double_t		t;
	t_vec3			N;
	bool			front_face;
} __attribute__((aligned(32))) t_hit;

typedef struct s_hit_ctx
{
	t_ray			*ray;
	t_interval		ray_t;
	t_hit			*record;
} __attribute__((aligned(32))) t_hit_ctx;

typedef struct s_quad_calc
{
	t_vec3			oc;
	double			a;
	double			half_b;
	double			c;
	double			d;
	double			root;
} __attribute__((aligned(32))) t_quad_calc;

typedef struct s_plane_calc
{
	double			denom;
	t_vec3			oc;
	double			t;
} __attribute__((aligned(32))) t_plane_calc;

static inline void	set_face_normal(t_hit *record, t_ray *ray,
		t_vec3 outward_normal)
{
	record->front_face = v3_dot(&ray->direction, &outward_normal) < 0.0;
	record->N = record->front_face ? outward_normal : v3_neg(outward_normal);
}

bool				hit(t_obj *obj, t_hit_ctx *ctx);
bool				hit_sphere(t_obj *sphere, t_hit_ctx *ctx);
bool				hit_cylinder(t_obj *cylinder, t_hit_ctx *ctx);
bool				hit_plane(t_obj *plane, t_hit_ctx *ctx);
bool				hit_plane_math(t_hit_ctx *ctx, t_vec3 center,
						t_vec3 normal);
#endif // MINIRT_INTERSECTION_H