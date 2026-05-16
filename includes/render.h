/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
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

bool	get_closest_hit(t_ray *r, t_world *w, t_hit *rec, t_vec3 *color);
t_vec3	phong_ray_color(t_ray *r, t_world *w);

#endif
