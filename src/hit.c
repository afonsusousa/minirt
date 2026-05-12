/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:32 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/12 22:59:31 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "intersection.h"
#include "../includes/intersection.h"
#include "obj.h"
#include "ray.h"
#include "stdbool.h"

bool hit(t_obj *obj, t_hit_ctx *ctx)
{
    t_hit temp_rec;
    t_hit_ctx temp_ctx = {ctx->ray, ctx->ray_t, &temp_rec};

    if (obj->type == OBJ_SPHERE)
    {
        if (hit_sphere(obj, &temp_ctx))
        {
            *(ctx->record) = temp_rec;
            return (true);
        }
    }
    else if (obj->type == OBJ_CYLINDER)
    {
        if (hit_cylinder(obj, &temp_ctx))
        {
            *(ctx->record) = temp_rec;
            return (true);
        }
    }
    else if (obj->type == OBJ_PLANE)
    {
        if (hit_plane(obj, &temp_ctx))
        {
            *(ctx->record) = temp_rec;
            return (true);
        }
    }
    return (false);
}
