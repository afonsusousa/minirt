#ifndef MINIRT_RENDER_H
#define MINIRT_RENDER_H

#include "obj.h"
#include "intersection.h"
#include "camera.h"

typedef struct s_phong_ctx
{
    t_vec3	tot;            // accumulated light
    t_vec3	l_dir;          // light direction
    double	dist;           // light distance
    t_vec3	v_dir;          // view direction
    t_vec3	ref_dir;        // reflected light direction
    double	shininess;      // specular strength
    t_vec3	specular_color; // specular tint
}	t_phong_ctx;

bool    get_closest_hit(t_ray *r, t_world *w, t_hit *rec, t_material **mat);
t_vec3	phong_ray_color(t_ray *r, t_world *w);
t_vec3  diffuse_ray_color(t_camera *c, t_ray *r, t_world *w, size_t bounce);

#endif
