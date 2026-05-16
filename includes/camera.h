#ifndef CAMERA_H
# define CAMERA_H

# include "obj.h"
# include "vec3.h"

void	init_camera(t_camera *cam, int image_width, double aspect_ratio);
t_ray	get_ray(t_camera *cam, int i, int j);

#endif
