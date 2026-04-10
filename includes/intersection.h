//
// Created by afonsusousa on 11/12/25.
//

#ifndef MINIRT_INTERSECTION_H
#define MINIRT_INTERSECTION_H

#include "vec3.h"
#include "obj.h"

typedef struct s_hit{
    t_vec3 p;
    double_t t;
    t_vec3 normal;
}t_hit;

double hit_sphere(t_obj *sphere, t_ray *ray);
#endif //MINIRT_INTERSECTION_H