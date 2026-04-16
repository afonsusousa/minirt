//
// Created by afonsusousa on 11/12/25.
//

#include <stdlib.h>
#include <stdbool.h>

#include "../includes/obj.h"
#include "../includes/ray.h"
#include "../includes/vec3.h"
#include "../includes/intersection.h"
//#include "../includes/interval.h"

/*
 t_vec3 N = v3_unit(v3_sub(ray_at(ray, tzao), world->pos));
        return (v3_muls(
            vec3(N.x + 1.0, N.y + 1.0, N.z + 1.0),
            0.5
*/
bool hit_sphere(t_obj *sphere, t_ray *ray, t_interval ray_t, t_hit *record)
{
    t_vec3	oc;
    double  a;
    double  h;
    double  c;
    double  d;
    double  root;

    oc = v3_sub(sphere->shape.sphere.center, ray->origin);
    a = v3_dot(ray->direction, ray->direction);
    h = v3_dot(ray->direction, oc);
    c = v3_dot(oc, oc) - sphere->shape.sphere.radius * sphere->shape.sphere.radius;
    d = h * h - a*c;
    if (d < 0)
        return (false);
    root = (h - sqrt(d)) / a;
    if (!surrounds(ray_t, root))
    {
        root = (h + sqrt(d)) / a;
        if (!surrounds(ray_t, root))
            return (false);
    }
    record->t = root;
    record->p = ray_at(ray, record->t);
    record->N = v3_unit(v3_divs(v3_sub(record->p, sphere->shape.sphere.center), sphere->shape.sphere.radius));
    return (true);
}