#include "../lib/minilibx-linux/mlx.h"
#include "../includes/mlx_mitm.h"
#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"
#include "../includes/obj.h"
#include "../includes/camera.h"
#include "../includes/intersection.h"
#include "../includes/interval.h"
#include "../includes/world.h"
#include <stdio.h>

t_color ray_color(t_ray *ray, t_world *world, size_t bounce)
{
    t_vec3 unit_direction = v3_unit(ray->direction);
    double a = 0.5 * (unit_direction.y + 1.0);
    (void)bounce;

    for (size_t i = 0; i < world->num_objects; i++)
    {
        t_hit record;
        if (hit(&world->objects[i], ray, (t_interval){0, INFINITY}, &record))
        {
            return (v3_muls(
                vec3(record.N.x + 1.0, record.N.y + 1.0, record.N.z + 1.0),
                0.5));
        }
    }

    // Sky gradient: white to blue
    return (v3_add(
        v3_muls(vec3(1.0, 1.0, 1.0), 1.0 - a),
        v3_muls(vec3(0.5, 0.7, 1.0), a)));
}

void my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img;
    t_world w;

    parse_file(&w, "exemplo.3d");

    init_camera(&w.camera, 1080, 16.0 / 9.0);
    img.width = w.camera.image_width;
    img.height = w.camera.image_height;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.width, img.height, "Hello world!");
    img.img = mlx_new_image(mlx, img.width, img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width; x++)
        {
            t_ray ray;
            ray.origin = w.camera.camera_center;
            ray.direction = v3_sub(
                v3_add(
                    w.camera.pixel00_loc,
                    v3_add(
                        v3_muls(w.camera.pixel_delta_u, x),
                        v3_muls(w.camera.pixel_delta_v, y))),
                w.camera.camera_center);

            my_mlx_pixel_put(&img, x, y, color_to_int(ray_color(&ray, &w, 1)));
        }
    }

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
