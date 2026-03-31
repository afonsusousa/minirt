//
// Created by afonsusousa on 11/12/25.
//

#include <stdlib.h>

#include "../includes/obj.h"
#include "../includes/ray.h"
#include "../includes/vec3.h"

double hit_sphere(t_obj *sphere, t_ray *ray)
{
    t_vec3	oc;
    double  a;
    double  b;
    double  c;
    double  d;

    oc = vec3_subtract(&sphere->pos, &ray->origin);
    a = vec3_dot(&ray->direction, &ray->direction);
    b = -2.0 * vec3_dot(&ray->direction, &oc);
    c = vec3_dot(&oc, &oc) - sphere->data.sphere.radius * sphere->data.sphere.radius;
    d = b * b - 4 * a *c;
    if (d < 0)
        return (-1.0);
    return ((-b - sqrt(d)) / (2.0*a));
}