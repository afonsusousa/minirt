#ifndef CAMERA_H
# define CAMERA_H

# include "vec3.h"
# include "obj.h"

void	init_camera(t_camera *cam, int image_width, double aspect_ratio);
t_ray	get_ray(t_camera *cam, int i, int j);

#endif
