#ifndef MINIRT_RENDER_H
# define MINIRT_RENDER_H

# include "camera.h"
# include "intersection.h"
# include "obj.h"

bool	get_closest_hit(t_ray *r, t_world *w, t_hit *rec, t_vec3 *color);
t_vec3	phong_ray_color(t_ray *r, t_world *w);

#endif
