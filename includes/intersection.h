//
// Created by afonsusousa on 11/12/25.
//

#ifndef MINIRT_INTERSECTION_H
#define MINIRT_INTERSECTION_H

#include "vec3.h"
#include "obj.h"

typedef struct intersection
{
    double  distance_squared;
    t_vec3  point;
    t_vec3  surface_normal;
    t_obj   *object;
    void    *context;
} intersection;

#endif //MINIRT_INTERSECTION_H