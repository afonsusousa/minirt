#ifndef CAMERA_H
# define CAMERA_H

# include "vec3.h"

typedef struct s_camera
{
    double  aspect_ratio;
    int     image_width;
    int     image_height;
    double  focal_length;
    double  viewport_height;
    double  viewport_width;
    t_vec3  camera_center;
    t_vec3  viewport_u;
    t_vec3  viewport_v;
    t_vec3  pixel_delta_u;
    t_vec3  pixel_delta_v;
    t_vec3  viewport_upper_left;
    t_vec3  pixel00_loc;
} t_camera;

void	init_camera(t_camera *cam, int image_width, double aspect_ratio);

#endif
