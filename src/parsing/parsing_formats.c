/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_formats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:58 by amagno-r          #+#    #+#             */
/*   Updated: 2026/04/25 18:56:58 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../includes/obj.h"
#include <stddef.h>

const t_format *get_sphere_fmt(void)
{
        static const t_format fmt[] = {
                { F_VEC3, offsetof(t_obj, shape.sphere.center), "pos" },
                { F_DOUBLE, offsetof(t_obj, shape.sphere.radius), "size" },
                { F_COLOR, 0, "color" },
                { F_OPT_MAT, 0, "material" },
                { F_END, 0, NULL }
        };
        return (fmt);
}

const t_format *get_plane_fmt(void)
{
        static const t_format fmt[] = {
                { F_VEC3, offsetof(t_obj, shape.plane.pos), "pos" },
                { F_VEC3, offsetof(t_obj, shape.plane.dir), "dir (normalized)" },
                { F_COLOR, 0, "color" },
                { F_OPT_MAT, 0, "material" },
                { F_END, 0, NULL }
        };
        return (fmt);
}

const t_format *get_cylinder_fmt(void)
{
        static const t_format fmt[] = {
                { F_VEC3, offsetof(t_obj, shape.cylinder.pos), "pos" },
                { F_VEC3, offsetof(t_obj, shape.cylinder.dir), "dir (normalized)" },
                { F_DOUBLE, offsetof(t_obj, shape.cylinder.radius), "size" },
                { F_DOUBLE, offsetof(t_obj, shape.cylinder.height), "height" },
                { F_COLOR, 0, "color" },
                { F_OPT_MAT, 0, "material" },
                { F_END, 0, NULL }
        };
        return (fmt);
}

const t_format *get_ambient_fmt(void)
{
        static const t_format fmt[] = {
                { F_DOUBLE, offsetof(t_ambient, ratio), "ratio" },
                { F_COLOR, offsetof(t_ambient, color), "color" },
                { F_END, 0, NULL }
        };
        return (fmt);
}

const t_format *get_camera_fmt(void)
{
        static const t_format fmt[] = {
                { F_VEC3, offsetof(t_camera, pos), "pos" },
                { F_VEC3, offsetof(t_camera, dir), "dir (normalized)" },
                { F_DOUBLE, offsetof(t_camera, fov), "fov" },
                { F_END, 0, NULL }
        };
        return (fmt);
}

const t_format *get_light_fmt(void)
{
        static const t_format fmt[] = {
                { F_VEC3, offsetof(t_light, pos), "pos" },
                { F_DOUBLE, offsetof(t_light, ratio), "ratio" },
                { F_COLOR, offsetof(t_light, color), "color" },
                { F_END, 0, NULL }
        };
        return (fmt);
}
