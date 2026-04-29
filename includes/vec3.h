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
/* creation */

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
    dest->w = 0.0;
}

static inline void v3_sub_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->x -= value->x;
    dest->y -= value->y;
    dest->z -= value->z;
    dest->w = 0.0;
}

static inline void v3_mul_mut(t_vec3 *dest, t_vec3 *value)
{
    dest->x *= value->x;
    dest->y *= value->y;
    dest->z *= value->z;
    dest->w = 0.0;
}

static inline void v3_muls_mut(t_vec3 *dest, double t)
{
    dest->x *= t;
    dest->y *= t;
    dest->z *= t;
    dest->w = 0.0;
}

static inline void v3_divs_mut(t_vec3 *dest, double t)
{
    dest->x /= t;
    dest->y /= t;
    dest->z /= t;
    dest->w = 0.0;
}

static inline void v3_neg_mut(t_vec3 *dest)
{
    dest->x = -dest->x;
    dest->y = -dest->y;
    dest->z = -dest->z;
    dest->w = 0.0;
}

static inline void v3_cross_mut(t_vec3 *dest, t_vec3 *value)
{
    double temp_x = dest->y * value->z - dest->z * value->y;
    double temp_y = dest->z * value->x - dest->x * value->z;
    double temp_z = dest->x * value->y - dest->y * value->x;
    dest->x = temp_x;
    dest->y = temp_y;
    dest->z = temp_z;
    dest->w = 0.0;
}

static inline void v3_reflect_mut(t_vec3 *dest, t_vec3 *n)
{
    double dot_prod = dest->x * n->x + dest->y * n->y + dest->z * n->z;
    dest->x -= 2.0 * dot_prod * n->x;
    dest->y -= 2.0 * dot_prod * n->y;
    dest->z -= 2.0 * dot_prod * n->z;
    dest->w = 0.0;
}

/* scalar & utility functions */

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
    double len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return (vec3(vec.x / len, vec.y / len, vec.z / len));
}

static inline double v3_dot(t_vec3 *a, t_vec3 *b)
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

// --- Fast RNG Setup (PCG32) ---
typedef struct s_pcg32_random {
    uint64_t state;
    uint64_t inc;
} t_pcg32_random;

// 32 bit random integer
static inline uint32_t pcg32_random_r(t_pcg32_random *rng) {
    uint64_t oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

// Random double in [0.0, 1.0)
// Multiply by 1.0 / (2^32)
static inline double pcg_double(t_pcg32_random *rng) {
    uint32_t raw = pcg32_random_r(rng);
    return raw * 2.3283064365386963e-10; 
}

static inline double pcg_range_double(t_pcg32_random *rng, double min, double max) {
    return min + (max - min) * pcg_double(rng);
}

static inline t_vec3 random_in_unit_sphere(t_pcg32_random *rng) {
    
    double len_sq;
    
    while (1) {
        t_vec3 p = vec3(
            pcg_range_double(rng, -1.0, 1.0),
            pcg_range_double(rng, -1.0, 1.0),
            pcg_range_double(rng, -1.0, 1.0)
        );
        
        len_sq = p.x * p.x + p.y * p.y + p.z * p.z;
        if (len_sq <= 1.0 && len_sq > BASICALLY_ZERO) {
            double root = sqrt(len_sq);
            p.x /= root;
            p.y /= root;
            p.z /= root;
            p.w = 0.0;
            return p;
        }
    }
}

static inline t_vec3 random_on_hemisphere(t_pcg32_random *rng,  t_vec3 *normal) 
{
    t_vec3 on_unit_sphere = random_in_unit_sphere(rng);
    if((on_unit_sphere.x * normal->x + on_unit_sphere.y * normal->y + on_unit_sphere.z * normal->z) > 0.0)
        return on_unit_sphere;
    else
    {
        on_unit_sphere.x = -on_unit_sphere.x;
        on_unit_sphere.y = -on_unit_sphere.y;
        on_unit_sphere.z = -on_unit_sphere.z;
        on_unit_sphere.w = 0.0;
        return on_unit_sphere;
    }
}

#endif //MINIRT_VEC3_H
