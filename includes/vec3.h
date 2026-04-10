//
// Created by afonsusousa on 11/9/25.
//

#ifndef MINIRT_VEC3_H
#define MINIRT_VEC3_H

#include <math.h>

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef t_vec3 t_point;

/* creation */

static inline t_vec3 vec3(double x, double y, double z)
{
    return ((t_vec3){x, y, z});
}

/* pure functions */

static inline t_vec3 v3_add(t_vec3 a, t_vec3 b)
{
    return (vec3(a.x + b.x,
                 a.y + b.y,
                 a.z + b.z));
}

static inline t_vec3 v3_sub(t_vec3 a, t_vec3 b)
{
    return (vec3(a.x - b.x,
                 a.y - b.y,
                 a.z - b.z));
}

static inline t_vec3 v3_mul(t_vec3 a, t_vec3 b)
{
    return (vec3(a.x * b.x,
                 a.y * b.y,
                 a.z * b.z));
}

static inline t_vec3 v3_muls(t_vec3 vec, double t)
{
    return (vec3(t * vec.x, t * vec.y, t * vec.z));
}

static inline t_vec3 v3_smul(double t, t_vec3 vec)
{
    return (v3_muls(vec, t));
}

static inline t_vec3 v3_divs(t_vec3 vec, double t)
{
    return (vec3(vec.x / t, vec.y / t, vec.z / t));
}

static inline t_vec3 v3_neg(t_vec3 vec)
{
    return (vec3(-vec.x, -vec.y, -vec.z));
}

static inline t_vec3 v3_reflect(t_vec3 v, t_vec3 n)
{
    t_vec3 scaled_n = v3_muls(n, 2 * (v.x * n.x + v.y * n.y + v.z * n.z));
    return (v3_sub(v, scaled_n));
}

static inline t_vec3 v3_cross(t_vec3 a, t_vec3 b)
{
    return (vec3(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x));
}

/* mutating functions */

static inline void v3_add_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->x += value->x;
    dest->y += value->y;
    dest->z += value->z;
}

static inline void v3_sub_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->x -= value->x;
    dest->y -= value->y;
    dest->z -= value->z;
}

static inline void v3_mul_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->x *= value->x;
    dest->y *= value->y;
    dest->z *= value->z;
}

static inline void v3_muls_mut(t_vec3 *dest, double t)
{
    dest->x *= t;
    dest->y *= t;
    dest->z *= t;
}

static inline void v3_divs_mut(t_vec3 *dest, double t)
{
    dest->x /= t;
    dest->y /= t;
    dest->z /= t;
}

static inline void v3_neg_mut(t_vec3 *dest)
{
    dest->x = -dest->x;
    dest->y = -dest->y;
    dest->z = -dest->z;
}

static inline void v3_cross_mut(t_vec3 *dest, t_vec3 *value)
{
    double temp_x = dest->y * value->z - dest->z * value->y;
    double temp_y = dest->z * value->x - dest->x * value->z;
    double temp_z = dest->x * value->y - dest->y * value->x;
    dest->x = temp_x;
    dest->y = temp_y;
    dest->z = temp_z;
}

static inline void v3_reflect_mut(t_vec3 *dest, t_vec3 *n)
{
    double dot_prod = dest->x * n->x + dest->y * n->y + dest->z * n->z;
    dest->x -= 2 * dot_prod * n->x;
    dest->y -= 2 * dot_prod * n->y;
    dest->z -= 2 * dot_prod * n->z;
}

/* scalar & utility functions */

static inline double v3_len_sq(t_vec3 vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
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
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}
static inline void v3_unit_mut(t_vec3 *dest)
{
    double length = sqrt(dest->x * dest->x + dest->y * dest->y + dest->z * dest->z);
    dest->x /= length;
    dest->y /= length;
    dest->z /= length;
}
static inline int v3_near_zero(t_vec3 vec)
{
    double s = 1e-8;
    return (fabs(vec.x) < s && fabs(vec.y) < s && fabs(vec.z) < s);
}

#endif //MINIRT_VEC3_H