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

static inline t_vec3 vec3(double x, double y, double z)
{
    return ((t_vec3){{x, y, z}});
}

static inline t_vec3  vec3_negative(const t_vec3 *vec)
{
        return (vec3(-vec->e[0], -vec->e[1], -vec->e[2]));
}

static inline t_vec3   vec3_sum(const t_vec3 *a, const t_vec3 *b)
{
    return (vec3(a->e[0] + b->e[0],
                 a->e[1] + b->e[1],
                 a->e[2] + b->e[2]));
}

static inline void   vec3_add(t_vec3 *dest, const t_vec3 *value)
{
    dest->e[0] += value->e[0];
    dest->e[1] += value->e[1];
    dest->e[2] += value->e[2];
}
static inline void   vec3_multiply(t_vec3 *dest, const t_vec3 *value)
{
    dest->e[0] *= value->e[0];
    dest->e[1] *= value->e[1];
    dest->e[2] *= value->e[2];
}

static inline void vec3_divide_scalar(t_vec3 *dest, const double t)
{
    dest->e[0] /= t;
    dest->e[1] /= t;
    dest->e[2] /= t;
}

static inline double vec3_length_squared(const t_vec3 *vec)
{
    return (vec->e[0] * vec->e[0] + vec->e[1] * vec->e[1] + vec->e[2] * vec->e[2]);
}

static inline double vec3_length(const t_vec3 *vec)
{
    return (sqrt(vec3_length_squared(vec)));
}

static inline t_vec3 vec3_subtract(const t_vec3 *a, const t_vec3 *b)
{
    return (vec3(a->e[0] - b->e[0],
                 a->e[1] - b->e[1],
                 a->e[2] - b->e[2]));
}

static inline t_vec3 vec3_multiply_vec(const t_vec3 *a, const t_vec3 *b)
{
    return (vec3(a->e[0] * b->e[0],
                 a->e[1] * b->e[1],
                 a->e[2] * b->e[2]));
}

static inline t_vec3 vec3_multiply_scalar(const t_vec3 *vec, double t)
{
    return (vec3(t * vec->e[0], t * vec->e[1], t * vec->e[2]));
}

static inline t_vec3 vec3_divide(const t_vec3 *vec, double t)
{
    return (vec3(vec->e[0] / t, vec->e[1] / t, vec->e[2] / t));
}

static inline double vec3_dot(const t_vec3 *a, const t_vec3 *b)
{
    return (a->e[0] * b->e[0]
         + a->e[1] * b->e[1]
         + a->e[2] * b->e[2]);
}

static inline t_vec3 vec3_cross(const t_vec3 *a, const t_vec3 *b)
{
    return (vec3(a->e[1] * b->e[2] - a->e[2] * b->e[1],
                 a->e[2] * b->e[0] - a->e[0] * b->e[2],
                 a->e[0] * b->e[1] - a->e[1] * b->e[0]));
}

static inline t_vec3 vec3_unit_vector(const t_vec3 *vec)
{
    return (vec3_divide(vec, vec3_length(vec)));
}

static inline t_vec3 vec3_scalar_multiply(double t, const t_vec3 *vec)
{
    return (vec3_multiply_scalar(vec, t));
}

static inline t_vec3 vec3_reflect(const t_vec3 *v, const t_vec3 *n)
{
    t_vec3 scaled_n = vec3_multiply_scalar(n, 2 * vec3_dot(v, n));
    return (vec3_subtract(v, &scaled_n));
}

static inline int vec3_near_zero(const t_vec3 *vec)
{
    const double s = 1e-8;
    return (fabs(vec->e[0]) < s && fabs(vec->e[1]) < s && fabs(vec->e[2]) < s);
}

#endif //MINIRT_VEC3_H