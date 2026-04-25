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

t_vec3 ray_color(t_camera *c, t_ray *r, t_world *world, size_t bounce)
{
    t_vec3 unit_direction = v3_unit(r->direction);
    double a = 0.5 * (unit_direction.y + 1.0);
    (void)bounce;

    for (size_t i = 0; i < world->num_objects; i++)
    {
        t_hit record;
        if (bounce <= 0)
            return (vec3(0, 0, 0));
        if (hit(&world->objects[i], r, (t_interval){0, INFINITY}, &record))
        {
            t_vec3 dir = random_on_hemisphere(&c->rng, &record.N);
            return (v3_muls(
                ray_color(c, &((t_ray) { record.p, dir}), world, bounce - 1),
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

    printf("w.camera.pixel00_loc: %f %f %f\n", w.camera.pixel00_loc.x, w.camera.pixel00_loc.y, w.camera.pixel00_loc.z);

    printf("w.camera.pixel00_loc: %f %f %f\n", w.camera.pixel00_loc.x, w.camera.pixel00_loc.y, w.camera.pixel00_loc.z);

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.width, img.height, "Hello world!");
    img.img = mlx_new_image(mlx, img.width, img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width; x++)
        {
            t_color pixel_color = vec3(0, 0, 0);
            for (int sample = 0; sample < w.camera.samples_per_pixel; sample++)
            {
                t_ray ray = get_ray(&w.camera, x, y);
                t_color sample_color = ray_color(&w.camera, &ray, &w, 50);
                v3_add_mut(&pixel_color, &sample_color);
            }
            v3_muls_mut(&pixel_color, w.camera.pixel_samples_scale);
            my_mlx_pixel_put(&img, x, y, color_to_int(pixel_color));
        }
    }

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
