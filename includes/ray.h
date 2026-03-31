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

    mult = vec3_multiply_scalar(&ray->direction, t);
    return (vec3_sum(&ray->origin, &mult));
}
#endif //MINIRT_RAY_H