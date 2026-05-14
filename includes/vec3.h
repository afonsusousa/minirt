//
// Created by afonsusousa on 11/9/25.
//

#ifndef MINIRT_VEC3_H
#define MINIRT_VEC3_H

#include <math.h>
#include <stdint.h>

typedef union s_vec3 {
    struct {
        double x;
        double y;
        double z;
        double w;
    };
    double e[4];
} t_vec3;

typedef t_vec3 t_point;
typedef t_vec3 t_color;

#define BASICALLY_ZERO 1e-160

static inline t_vec3 vec3(double x, double y, double z) {
    t_vec3 res;
    res.x = x; 
    res.y = y; 
    res.z = z;
    res.w = 0.0;
    return res;
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

static inline t_vec3    v3_sq(t_vec3 a) {
    return v3_mul(a, a);
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
    t_vec3 scaled_n = v3_muls(n, 2.0 * (v.x * n.x + v.y * n.y + v.z * n.z));
    return (v3_sub(v, scaled_n));
}

static inline double v3_dot(const t_vec3 *a, const t_vec3 *b);
static inline double v3_len_sq(t_vec3 vec);

static inline t_vec3 v3_refract(t_vec3 v, t_vec3 n, double ri)
{
    t_vec3 neg_v = v3_neg(v);
    double cos_theta = fmin(v3_dot(&neg_v, &n), 1.0);
    t_vec3 r_out_perp = v3_muls(v3_add(v, v3_muls(n, cos_theta)), ri);
    t_vec3 r_out_parallel = v3_muls(n, -sqrt(fabs(1.0 - v3_len_sq(r_out_perp))));
    return (v3_add(r_out_perp, r_out_parallel));
}

static inline double v3_reflectance(double cosine, double ref_idx)
{
    double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    r0 = r0 * r0;
    cosine = 1.0 - cosine;
    return r0 + (1.0 - r0) * cosine * cosine * cosine * cosine * cosine;
}

static inline t_vec3 v3_cross(t_vec3 a, t_vec3 b)
{
    return (vec3(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x));
}

static inline double v3_len_sq(t_vec3 vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

static inline double v3_len(t_vec3 vec)
{
    return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

static inline t_vec3 v3_unit(t_vec3 vec)
{
    double len = sqrt(v3_len_sq(vec));
    return (vec3(vec.x / len, vec.y / len, vec.z / len));
}

static inline double v3_dot(const t_vec3 *a, const t_vec3 *b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z);
}

static inline void v3_unit_mut(t_vec3 *dest)
{
    double length = sqrt(dest->x * dest->x + dest->y * dest->y + dest->z * dest->z);
    dest->x /= length;
    dest->y /= length;
    dest->z /= length;
    dest->w = 0.0;
}

static inline int v3_near_zero(t_vec3 vec)
{
    double s = 1e-8;
    return (fabs(vec.x) < s && fabs(vec.y) < s && fabs(vec.z) < s);
}

#endif //MINIRT_VEC3_H
