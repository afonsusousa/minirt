//
// Created by afonsusousa on 11/9/25.
//

#ifndef MINIRT_VEC3_H
#define MINIRT_VEC3_H

#include <math.h>

typedef union
{
    double at[3];
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

static inline t_vec3 v3_add(t_vec3 a, t_vec3 b)
{
    return (vec3(a.at[0] + b.at[0],
                 a.at[1] + b.at[1],
                 a.at[2] + b.at[2]));
}

static inline t_vec3 v3_sub(t_vec3 a, t_vec3 b)
{
    return (vec3(a.at[0] - b.at[0],
                 a.at[1] - b.at[1],
                 a.at[2] - b.at[2]));
}

static inline t_vec3 v3_mul(t_vec3 a, t_vec3 b)
{
    return (vec3(a.at[0] * b.at[0],
                 a.at[1] * b.at[1],
                 a.at[2] * b.at[2]));
}

static inline t_vec3 v3_muls(t_vec3 vec, double t)
{
    return (vec3(t * vec.at[0], t * vec.at[1], t * vec.at[2]));
}

static inline t_vec3 v3_smul(double t, t_vec3 vec)
{
    return (v3_muls(vec, t));
}

static inline t_vec3 v3_divs(t_vec3 vec, double t)
{
    return (vec3(vec.at[0] / t, vec.at[1] / t, vec.at[2] / t));
}

static inline t_vec3 v3_neg(t_vec3 vec)
{
    return (vec3(-vec.at[0], -vec.at[1], -vec.at[2]));
}

static inline t_vec3 v3_reflect(t_vec3 v, t_vec3 n)
{
    t_vec3 scaled_n = v3_muls(n, 2 * (v.at[0] * n.at[0] + v.at[1] * n.at[1] + v.at[2] * n.at[2]));
    return (v3_sub(v, scaled_n));
}

static inline t_vec3 v3_cross(t_vec3 a, t_vec3 b)
{
    return (vec3(a.at[1] * b.at[2] - a.at[2] * b.at[1],
                 a.at[2] * b.at[0] - a.at[0] * b.at[2],
                 a.at[0] * b.at[1] - a.at[1] * b.at[0]));
}

/* mutating functions */

static inline void v3_add_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->at[0] += value->at[0];
    dest->at[1] += value->at[1];
    dest->at[2] += value->at[2];
}

static inline void v3_sub_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->at[0] -= value->at[0];
    dest->at[1] -= value->at[1];
    dest->at[2] -= value->at[2];
}

static inline void v3_mul_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->at[0] *= value->at[0];
    dest->at[1] *= value->at[1];
    dest->at[2] *= value->at[2];
}

static inline void v3_muls_mut(t_vec3 *dest, double t)
{
    dest->at[0] *= t;
    dest->at[1] *= t;
    dest->at[2] *= t;
}

static inline void v3_divs_mut(t_vec3 *dest, double t)
{
    dest->at[0] /= t;
    dest->at[1] /= t;
    dest->at[2] /= t;
}

static inline void v3_neg_mut(t_vec3 *dest)
{
    dest->at[0] = -dest->at[0];
    dest->at[1] = -dest->at[1];
    dest->at[2] = -dest->at[2];
}

static inline void v3_cross_mut(t_vec3 *dest, t_vec3 *value)
{
    double temp_x = dest->at[1] * value->at[2] - dest->at[2] * value->at[1];
    double temp_y = dest->at[2] * value->at[0] - dest->at[0] * value->at[2];
    double temp_z = dest->at[0] * value->at[1] - dest->at[1] * value->at[0];
    dest->at[0] = temp_x;
    dest->at[1] = temp_y;
    dest->at[2] = temp_z;
}

static inline void v3_reflect_mut(t_vec3 *dest, t_vec3 *n)
{
    double dot_prod = dest->at[0] * n->at[0] + dest->at[1] * n->at[1] + dest->at[2] * n->at[2];
    dest->at[0] -= 2 * dot_prod * n->at[0];
    dest->at[1] -= 2 * dot_prod * n->at[1];
    dest->at[2] -= 2 * dot_prod * n->at[2];
}

/* scalar & utility functions */

static inline double v3_len_sq(t_vec3 vec)
{
    return (vec.at[0] * vec.at[0] + vec.at[1] * vec.at[1] + vec.at[2] * vec.at[2]);
}

static inline double v3_len(t_vec3 vec)
{
    return (sqrt(v3_len_sq(vec)));
}

static inline t_vec3 v3_unit(t_vec3 vec)
{
    return (v3_divs(vec, v3_len(vec)));
}

static inline double v3_dot(t_vec3 a, t_vec3 b)
{
    return (a.at[0] * b.at[0] + a.at[1] * b.at[1] + a.at[2] * b.at[2]);
}
static inline void v3_unit_mut(t_vec3 *dest)
{
    double length = sqrt(dest->at[0] * dest->at[0] + dest->at[1] * dest->at[1] + dest->at[2] * dest->at[2]);
    dest->at[0] /= length;
    dest->at[1] /= length;
    dest->at[2] /= length;
}
static inline int v3_near_zero(t_vec3 vec)
{
    double s = 1e-8;
    return (fabs(vec.at[0]) < s && fabs(vec.at[1]) < s && fabs(vec.at[2]) < s);
}

#endif //MINIRT_VEC3_H