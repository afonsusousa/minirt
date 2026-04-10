//
// Created by afonsusousa on 11/12/25.
//

#include <stdlib.h>

#include "../includes/obj.h"
#include "../includes/ray.h"
#include "../includes/vec3.h"
#include "../includes/intersection.h"

double hit_sphere(t_obj *sphere, t_ray *ray)
{
    t_vec3	oc;
    double  a;
    double  h;
    double  c;
    double  d;

    oc = v3_sub(sphere->pos, ray->origin);
    a = v3_dot(ray->direction, ray->direction);
    h = v3_dot(ray->direction, oc);
    c = v3_dot(oc, oc) - sphere->data.sphere.radius * sphere->data.sphere.radius;
    d = h * h - a*c;
    if (d < 0)
        return (-1.0);
    return ((h - sqrt(d)) / a);
}