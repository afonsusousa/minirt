/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:29:16 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:29:17 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "ray.h"
# include "stdbool.h"
# include "stddef.h"
# include "vec3.h"
# include <stdint.h>

typedef enum e_obj_type
{
	OBJ_AMBIENT = 1,
	OBJ_CAMERA,
	OBJ_LIGHT,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	ERR
}	t_obj_type;

typedef enum e_field_type
{
	F_NVEC3,
	F_VEC3,
	F_DOUBLE,
	F_COLOR,
	F_END
}	t_field_type;

typedef struct s_format
{
	t_field_type	type;
	size_t			offset;
	const char		*name;
}	t_format;

struct	s_hit;
struct	s_ray;
struct	s_world;
struct	s_camera;

typedef struct s_phong_ctx
{
	struct s_world	*world;
	struct s_hit	*record;
	t_vec3			obj_color;
	struct s_ray	*ray;
}					t_phong_ctx;

typedef struct s_obj
{
	t_obj_type		type;
	t_vec3			color;

	union
	{
		struct
		{
			t_vec3	center;
			double	radius;
		}	s_sphere;
		struct
		{
			t_vec3	pos;
			t_vec3	dir;
		}	s_plane;
		struct
		{
			t_vec3	pos;
			t_vec3	dir;
			double	radius;
			double	height;
		}	s_cylinder;
	}	u_shape;
}	t_obj;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			dir;
	double			fov;

	int				image_width;
	int				image_height;
	t_vec3			camera_center;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
	t_vec3			pixel00_loc;
	int				samples_per_pixel;
	double			pixel_samples_scale;
}	t_camera;

typedef struct s_light
{
	t_vec3			pos;
	double			ratio;
	t_vec3			color;
}	t_light;

typedef struct s_ambient
{
	double			ratio;
	t_vec3			color;
}	t_ambient;

typedef struct s_world
{
	t_obj			*objects;
	size_t			num_objects;

	t_camera		camera;
	t_ambient		ambient;
	t_light			*lights;
	size_t			num_lights;
	bool			has_camera;
	bool			has_ambient;
}	t_world;

#endif
