/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:29:43 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:29:44 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "obj.h"
# include "vec3.h"

void	init_camera(t_camera *cam, int image_width, double aspect_ratio);
t_ray	get_ray(t_camera *cam, int i, int j);

#endif
