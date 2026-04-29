/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:35 by amagno-r          #+#    #+#             */
/*   Updated: 2026/04/25 18:56:36 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"

static t_vec3	get_u(t_vec3 dir)
{
	t_vec3	vup;

	vup = vec3(0, 1, 0);
	if (fabs(dir.y) == 1.0 && dir.x == 0.0 && dir.z == 0.0)
		vup = vec3(0, 0, 1);
	return (v3_unit(v3_cross(vup, v3_unit(dir))));
}

static t_vec3	get_v(t_vec3 dir)
{
	return (v3_cross(v3_unit(dir), get_u(dir)));
}

static void	init_steps(t_camera *cam, double v_width, double v_height)
{
	t_vec3	viewport_u;
	t_vec3	viewport_v;

	viewport_u = v3_muls(get_u(cam->dir), v_width);
	viewport_v = v3_muls(get_v(cam->dir), -v_height);
	cam->pixel_delta_u = v3_divs(viewport_u, cam->image_width);
	cam->pixel_delta_v = v3_divs(viewport_v, cam->image_height);
}

static void	set_viewport_origin(t_camera *cam, double v_w, double v_h)
{
	t_vec3	vp_u;
	t_vec3	vp_v;
	t_vec3	vp_upper_left;

	vp_u = v3_muls(get_u(cam->dir), v_w);
	vp_v = v3_muls(get_v(cam->dir), -v_h);
	vp_upper_left = v3_sub(
			v3_sub(
				v3_add(cam->camera_center, v3_unit(cam->dir)),
				v3_divs(vp_u, 2.0)),
			v3_divs(vp_v, 2.0));
	cam->pixel00_loc = v3_add(
			vp_upper_left,
			v3_muls(
				v3_add(cam->pixel_delta_u, cam->pixel_delta_v),
				0.5));
}

static t_vec3 sample_square(t_camera *cam)
{
	return vec3(
		pcg_double(&cam->rng) - 0.5,
		pcg_double(&cam->rng) - 0.5,
		0
	);
}

t_ray get_ray(t_camera *cam, int i, int j)
{
	t_vec3 offset;
	t_vec3 pixel_sample;
	t_vec3 ray_origin;
	t_vec3 ray_direction;
	
	offset = sample_square(cam);
	pixel_sample = v3_add(
		cam->pixel00_loc,
		v3_add(
			v3_muls(cam->pixel_delta_u, i + offset.x),
			v3_muls(cam->pixel_delta_v, j + offset.y)
		)
	);
	
	ray_origin = cam->camera_center;
	ray_direction = v3_sub(pixel_sample, ray_origin);
	
	return ((t_ray){ray_origin, ray_direction});
}

void	init_camera(t_camera *cam, int image_width, double aspect_ratio)
{
	double	v_width;
	double	v_height;

	cam->samples_per_pixel = 100;
	cam->pixel_samples_scale = 1.0 / cam->samples_per_pixel;
	cam->rng.state = 0x853c49e6748fea9bULL;
	cam->rng.inc = 0xda3e39cb94b95bdbULL;

	cam->image_width = image_width;
	cam->image_height = (int)(cam->image_width / aspect_ratio);
	if (cam->image_height < 1)
		cam->image_height = 1;
	cam->camera_center = cam->pos;
	if (cam->fov >= 180.0)
		cam->fov = 179.9;
	v_width = 2.0 * tan((cam->fov * (M_PI / 180.0)) / 2.0);
	v_height = v_width / aspect_ratio;
	init_steps(cam, v_width, v_height);
	set_viewport_origin(cam, v_width, v_height);
}
