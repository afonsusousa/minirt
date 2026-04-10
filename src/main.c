#include "../lib/minilibx-linux/mlx.h"
#include "../includes/mlx_mitm.h"
#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"
#include "../includes/obj.h"
#include "../includes/camera.h"
#include "../includes/intersection.h"
#include <stdio.h>

t_color ray_color(t_ray *ray, t_obj *world, size_t bounce)
{
    t_vec3 unit_direction = v3_unit(ray->direction);
    double a = 0.5 * (unit_direction.y + 1.0);
    t_hit record;
    (void)bounce;

    if (hit_sphere(world, ray, &record))
    {
        return (v3_muls(
            vec3(record.N.x + 1.0, record.N.y + 1.0, record.N.z + 1.0),
            0.5
        ));
    }

    // Sky gradient: white to blue
    return (v3_add(
        v3_muls(vec3(1.0, 1.0, 1.0), 1.0 - a),
        v3_muls(vec3(0.5, 0.7, 1.0), a)
    ));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
    void	*mlx;
    void	*mlx_win;
    t_data	img;
    t_camera	cam;

    init_camera(&cam, 1080, 16.0 / 9.0);
    img.width = cam.image_width;
    img.height = cam.image_height;
    
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.width, img.height, "Hello world!");
    img.img = mlx_new_image(mlx, img.width, img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                &img.endian);

    t_obj sph;
    sph.pos = vec3(0,0,1); // moved forward slightly to be visible
    sph.data.sphere.radius = 0.5;

    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width; x++)
        {
            t_ray ray;
            ray.origin = cam.camera_center;
            ray.direction = v3_sub(
                v3_add(
                    cam.pixel00_loc,
                    v3_add(
                        v3_muls(cam.pixel_delta_u, x),
                        v3_muls(cam.pixel_delta_v, y)
                    )
                ),
                cam.camera_center
            );
            
            my_mlx_pixel_put(&img, x, y, color_to_int(ray_color(&ray, &sph, 1)));
        }
    }

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
