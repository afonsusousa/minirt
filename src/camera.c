#include "../includes/camera.h"

static void     init_steps(t_camera *cam)
{
        cam->viewport_u = vec3(cam->viewport_width, 0, 0);
        cam->viewport_v = vec3(0, -cam->viewport_height, 0);
        cam->pixel_delta_u = v3_divs(cam->viewport_u, cam->image_width);
        cam->pixel_delta_v = v3_divs(cam->viewport_v, cam->image_height);
}

static void     set_viewport_origin(t_camera *cam)
{
        cam->viewport_upper_left = v3_sub(
                v3_sub(
                        v3_sub(cam->camera_center, vec3(0, 0, cam->focal_length)),
                        v3_divs(cam->viewport_u, 2.0)
                ),
                v3_divs(cam->viewport_v, 2.0)
        );

        cam->pixel00_loc = v3_add(
                cam->viewport_upper_left,
                v3_muls(
                        v3_add(cam->pixel_delta_u, cam->pixel_delta_v),
                        0.5
                )
        );
}

void    init_camera(t_camera *cam, int image_width, double aspect_ratio)
{
        cam->aspect_ratio = aspect_ratio;
        cam->image_width = image_width;
        cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
        if (cam->image_height < 1)
                cam->image_height = 1;
        cam->focal_length = 1.0;
        cam->viewport_height = 2.0;
        cam->viewport_width = cam->viewport_height * ((double)cam->image_width / cam->image_height);
        cam->camera_center = vec3(0, 0, 0);
        init_steps(cam);
        set_viewport_origin(cam);
}
