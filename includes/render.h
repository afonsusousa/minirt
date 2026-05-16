/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:29:01 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:29:01 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "camera.h"
# include "intersection.h"
# include "obj.h"

# define SHININESS 32.0
# define SPEC_INTENSITY 1.0

bool	get_closest_hit(t_ray *r, t_world *w, t_hit *rec, t_vec3 *color);
t_vec3	phong_ray_color(t_ray *r, t_world *w);
t_vec3	calc_ambient(t_phong_ctx *ctx);
t_vec3	calc_diffuse(t_phong_ctx *ctx, t_vec3 l_dir, size_t idx);
t_vec3	calc_specular(t_phong_ctx *ctx, t_vec3 l_dir, size_t idx);

#endif
