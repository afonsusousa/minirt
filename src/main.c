/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:55:59 by amagno-r          #+#    #+#             */
/*   Updated: 2026/04/29 19:13:59 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static bool get_closest_hit(t_ray *r, t_world *world, t_hit *closest_record, t_material **closest_mat)
{
    t_hit record;
    bool hit_anything;
    double closest_so_far;
    size_t i;

    hit_anything = false;
    closest_so_far = INFINITY;
    i = 0;
    while (i < world->num_objects)
    {
        if (hit(&world->objects[i], r, (t_interval){0.001, closest_so_far}, &record))
        {
            hit_anything = true;
            closest_so_far = record.t;
            *closest_record = record;
            *closest_mat = &world->materials[world->objects[i].mat_idx];
        }
        i++;
    }
    return (hit_anything);
}

t_vec3 ray_color(t_camera *c, t_ray *r, t_world *world, size_t bounce)
{
    t_hit closest_record;
    t_material *closest_mat;
    t_ray scattered;
    t_vec3 unit_dir;
    double a;

    if (bounce <= 0)
        return (vec3(0, 0, 0));
    if (get_closest_hit(r, world, &closest_record, &closest_mat))
    {
        scattered.direction = r->direction;
        unit_dir = closest_mat->color;
        //false here is hacky af
        v3_muls_mut(&unit_dir, 
            0.5 + (0.5 * closest_mat->scatter(c, &closest_record, &scattered, closest_mat)));
        return (v3_mul(ray_color(c, &scattered, world, bounce - 1), unit_dir));
    }
    unit_dir = v3_unit(r->direction);
    a = 0.5 * (unit_dir.y + 1.0);
    return (v3_add(v3_muls(vec3(1.0, 1.0, 1.0), 1.0 - a),
                   v3_muls(vec3(0.5, 0.7, 1.0), a)));
}

void my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char *dst;
    if (data->height < y || y < 0)
        return ;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img;
    t_world w __attribute__((aligned(32)));

    parse_file(&w, "exemplo2.3d");

    assign_material_scatter_funcs(&w);

    init_camera(&w.camera, 1920, 16.0 / 9.0);
    img.width = w.camera.image_width;
    img.height = w.camera.image_height;

    printf("w.camera.pixel00_loc: %f %f %f\n", w.camera.pixel00_loc.x, w.camera.pixel00_loc.y, w.camera.pixel00_loc.z);

    printf("w.camera.pixel00_loc: %f %f %f\n", w.camera.pixel00_loc.x, w.camera.pixel00_loc.y, w.camera.pixel00_loc.z);

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.width, img.height, "Hello world!");
    img.img = mlx_new_image(mlx, img.width, img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

    // for (int y = 0; y < img.height; y++)
    // {
    //     for (int x = 0; x < img.width; x++)
    //     {
    //         t_color pixel_color = vec3(0, 0, 0);
    //         for (int sample = 0; sample < w.camera.samples_per_pixel; sample++)
    //         {
    //             t_ray ray = get_ray(&w.camera, x, y);
    //             t_color sample_color = ray_color(&w.camera, &ray, &w, 50);
    //             v3_add_mut(&pixel_color, &sample_color);
    //         }
    //         v3_muls_mut(&pixel_color, w.camera.pixel_samples_scale);
    //         my_mlx_pixel_put(&img, x, y, color_to_int(pixel_color));
    //     }
    // }

    for (int chunk_y = 0; chunk_y < img.height; chunk_y += 16)
    {
        for (int chunk_x = 0; chunk_x < img.width; chunk_x += 16)
        {
            for (int y = 0; y < 16; y++)
            {
                for (int x = 0; x < 16; x++)
                {
                    int px = chunk_x + x;
                    int py = chunk_y + y;

                    if (px >= img.width || py >= img.height)
                        continue;
                    t_color pixel_color = vec3(0, 0, 0);
                    for (int sample = 0; sample < w.camera.samples_per_pixel; sample++)
                    {
                        t_ray ray = get_ray(&w.camera, px, py);
                        t_color sample_color = ray_color(&w.camera, &ray, &w, 100);
                        v3_add_mut(&pixel_color, &sample_color);
                    }
                    v3_muls_mut(&pixel_color, w.camera.pixel_samples_scale);
                    my_mlx_pixel_put(&img, px, py, color_to_int(pixel_color));
                }
            }

            mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
        }
    }
    mlx_loop(mlx);
}
