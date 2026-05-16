/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:29:05 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:29:07 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RAY_H
# define MINIRT_RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_vec3				origin;
	t_vec3				direction;
} __attribute__((aligned(32))) t_ray;

static inline t_vec3	ray_at(t_ray *ray, double t)
{
	t_vec3	mult;

	mult = v3_muls(ray->direction, t);
	return (v3_add(ray->origin, mult));
}
#endif // MINIRT_RAY_H