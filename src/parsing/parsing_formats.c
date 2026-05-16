/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_formats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:44:07 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:44:08 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/obj.h"
#include "parsing.h"
#include <stddef.h>

const t_format	*get_sphere_fmt(void)
{
	static const t_format	fmt[] = {
	{F_VEC3, offsetof(t_obj, u_shape.s_sphere.center), "pos"},
	{F_DOUBLE, offsetof(t_obj, u_shape.s_sphere.radius), "size"},
	{F_COLOR, offsetof(t_obj, color), "color"},
	{F_END, 0, NULL}
	};
	return (fmt);
}

const t_format	*get_plane_fmt(void)
{
	static const t_format	fmt[] = {
	{F_VEC3, offsetof(t_obj, u_shape.s_plane.pos), "pos"},
	{F_NVEC3, offsetof(t_obj, u_shape.s_plane.dir), "dir (normalized)"},
	{F_COLOR, offsetof(t_obj, color), "color"},
	{F_END, 0, NULL}
	};
	return (fmt);
}

const t_format	*get_cylinder_fmt(void)
{
	static const t_format	fmt[] = {
	{F_VEC3, offsetof(t_obj, u_shape.s_cylinder.pos), "pos"},
	{F_NVEC3, offsetof(t_obj, u_shape.s_cylinder.dir), "dir (normalized)"},
	{F_DOUBLE, offsetof(t_obj, u_shape.s_cylinder.radius), "size"},
	{F_DOUBLE, offsetof(t_obj, u_shape.s_cylinder.height), "height"},
	{F_COLOR, offsetof(t_obj, color), "color"},
	{F_END, 0, NULL}
	};
	return (fmt);
}

const t_format	*get_ambient_fmt(void)
{
	static const t_format	fmt[] = {
	{F_DOUBLE, offsetof(t_ambient, ratio), "ratio"},
	{F_COLOR, offsetof(t_ambient, color), "color"},
	{F_END, 0, NULL}
	};
	return (fmt);
}

const t_format	*get_camera_fmt(void)
{
	static const t_format	fmt[] = {
	{F_VEC3, offsetof(t_camera, pos), "pos"},
	{F_NVEC3, offsetof(t_camera, dir), "dir (normalized)"},
	{F_DOUBLE, offsetof(t_camera, fov), "fov"},
	{F_END, 0, NULL}
	};
	return (fmt);
}
