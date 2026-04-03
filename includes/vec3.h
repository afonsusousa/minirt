//
// Created by afonsusousa on 11/9/25.
//

#ifndef MINIRT_VEC3_H
#define MINIRT_VEC3_H

#include <math.h>

typedef union
{
    double e[3];
    struct
    {
        double x;
        double y;
        double z;
    } v;
} t_vec3;

typedef t_vec3 t_point;

/* creation */

static inline t_vec3 vec3(double x, double y, double z)
{
    return ((t_vec3){{x, y, z}});
}

/* pure functions */

static inline t_vec3 v3_add(t_vec3 *a, t_vec3 *b)
{
    return (vec3(a->e[0] + b->e[0],
                 a->e[1] + b->e[1],
                 a->e[2] + b->e[2]));
}

static inline t_vec3 v3_sub(t_vec3 *a, t_vec3 *b)
{
    return (vec3(a->e[0] - b->e[0],
                 a->e[1] - b->e[1],
                 a->e[2] - b->e[2]));
}

static inline t_vec3 v3_mul(t_vec3 *a, t_vec3 *b)
{
    return (vec3(a->e[0] * b->e[0],
                 a->e[1] * b->e[1],
                 a->e[2] * b->e[2]));
}

static inline t_vec3 v3_muls(t_vec3 *vec, double t)
{
    return (vec3(t * vec->e[0], t * vec->e[1], t * vec->e[2]));
}

static inline t_vec3 v3_smul(double t, t_vec3 *vec)
{
    return (v3_muls(vec, t));
}

static inline t_vec3 v3_divs(t_vec3 *vec, double t)
{
    return (vec3(vec->e[0] / t, vec->e[1] / t, vec->e[2] / t));
}

static inline t_vec3 v3_neg(t_vec3 *vec)
{
    return (vec3(-vec->e[0], -vec->e[1], -vec->e[2]));
}

static inline t_vec3 v3_reflect(t_vec3 *v, t_vec3 *n)
{
    t_vec3 scaled_n = v3_muls(n, 2 * (v->e[0] * n->e[0] + v->e[1] * n->e[1] + v->e[2] * n->e[2]));
    return (v3_sub(v, &scaled_n));
}

static inline t_vec3 v3_cross(t_vec3 *a, t_vec3 *b)
{
    return (vec3(a->e[1] * b->e[2] - a->e[2] * b->e[1],
                 a->e[2] * b->e[0] - a->e[0] * b->e[2],
                 a->e[0] * b->e[1] - a->e[1] * b->e[0]));
}

/* mutating functions */

static inline void v3_add_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->e[0] += value->e[0];
    dest->e[1] += value->e[1];
    dest->e[2] += value->e[2];
}

static inline void v3_sub_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->e[0] -= value->e[0];
    dest->e[1] -= value->e[1];
    dest->e[2] -= value->e[2];
}

static inline void v3_mul_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->e[0] *= value->e[0];
    dest->e[1] *= value->e[1];
    dest->e[2] *= value->e[2];
}

static inline void v3_muls_mut(t_vec3 *dest, double t)
{
    dest->e[0] *= t;
    dest->e[1] *= t;
    dest->e[2] *= t;
}

static inline void v3_divs_mut(t_vec3 *dest, double t)
{
    dest->e[0] /= t;
    dest->e[1] /= t;
    dest->e[2] /= t;
}

static inline void v3_neg_mut(t_vec3 *dest)
{
    dest->e[0] = -dest->e[0];
    dest->e[1] = -dest->e[1];
    dest->e[2] = -dest->e[2];
}

static inline void v3_cross_mut(t_vec3 *dest, t_vec3 *value)
{
    double temp_x = dest->e[1] * value->e[2] - dest->e[2] * value->e[1];
    double temp_y = dest->e[2] * value->e[0] - dest->e[0] * value->e[2];
    double temp_z = dest->e[0] * value->e[1] - dest->e[1] * value->e[0];
    dest->e[0] = temp_x;
    dest->e[1] = temp_y;
    dest->e[2] = temp_z;
}

static inline void v3_reflect_mut(t_vec3 *dest, t_vec3 *n)
{
    double dot_prod = dest->e[0] * n->e[0] + dest->e[1] * n->e[1] + dest->e[2] * n->e[2];
    dest->e[0] -= 2 * dot_prod * n->e[0];
    dest->e[1] -= 2 * dot_prod * n->e[1];
    dest->e[2] -= 2 * dot_prod * n->e[2];
}

/* scalar & utility functions */

static inline double v3_len_sq(t_vec3 *vec)
{
    return (vec->e[0] * vec->e[0] + vec->e[1] * vec->e[1] + vec->e[2] * vec->e[2]);
}

static inline double v3_len(t_vec3 *vec)
{
    return (sqrt(v3_len_sq(vec)));
}

static inline t_vec3 v3_unit(t_vec3 *vec)
{
    return (v3_divs(vec, v3_len(vec)));
}

static inline double v3_dot(t_vec3 *a, t_vec3 *b)
{
    return (a->e[0] * b->e[0] + a->e[1] * b->e[1] + a->e[2] * b->e[2]);
}
static inline void v3_unit_mut(t_vec3 *dest)
{
    double length = sqrt(dest->e[0] * dest->e[0] + dest->e[1] * dest->e[1] + dest->e[2] * dest->e[2]);
    dest->e[0] /= length;
    dest->e[1] /= length;
    dest->e[2] /= length;
}
static inline int v3_near_zero(t_vec3 *vec)
{
    double s = 1e-8;
    return (fabs(vec->e[0]) < s && fabs(vec->e[1]) < s && fabs(vec->e[2]) < s);
}

#endif //MINIRT_VEC3_H