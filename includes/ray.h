//
// Created by afonsusousa on 11/12/25.
//

#ifndef MINIRT_RAY_H
#define MINIRT_RAY_H

#include "vec3.h"

typedef struct s_ray
{
    t_vec3  origin;
    t_vec3  direction;
} t_ray;

static inline t_vec3 ray_at(t_ray *ray, double t)
{
    t_vec3  mult;

    mult = v3_muls(&ray->direction, t);
    return (v3_add(&ray->origin, &mult));
}
#endif //MINIRT_RAY_H