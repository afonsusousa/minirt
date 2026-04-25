/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:32 by amagno-r          #+#    #+#             */
/*   Updated: 2026/04/25 18:56:32 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "intersection.h"
#include "../includes/intersection.h"
#include "obj.h"
#include "ray.h"
#include "stdbool.h"

bool    hit(t_obj *obj, t_ray *ray, t_interval ray_t, t_hit *rec)
{
    t_hit temp_rec;
//    bool hit_anything;
 //   double closest_so_far;

    //hit_anything = false;
    //closest_so_far = ray_t.max;
    if (obj->type == OBJ_SPHERE)
    {
        if(hit_sphere(obj, ray, ray_t, &temp_rec))
        {
  //          hit_anything = true;
   //         closest_so_far = temp_rec.t;
            *rec = temp_rec;
            return (true);
        }
    }
    return (false);
}
