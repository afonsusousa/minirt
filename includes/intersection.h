//
// Created by afonsusousa on 11/12/25.
//

#ifndef MINIRT_INTERSECTION_H
#define MINIRT_INTERSECTION_H

#include "vec3.h"
#include "obj.h"
#include "../includes/interval.h"
#include <stdbool.h>

typedef struct s_hit{
    t_vec3 p;
    double_t t;
    t_vec3 N;
    bool front_face;
} __attribute__((aligned(32))) t_hit;

static inline void set_face_normal(t_hit *record, t_ray *ray, t_vec3 outward_normal)
{
    record->front_face = v3_dot(&ray->direction, &outward_normal) < 0.0;
    record->N = record->front_face ? outward_normal : v3_neg(outward_normal);
}

bool hit(t_obj *obj, t_ray *ray, t_interval intl, t_hit *rec);
bool hit_sphere(t_obj *sphere, t_ray *ray, t_interval intl, t_hit *record);
#endif //MINIRT_INTERSECTION_H