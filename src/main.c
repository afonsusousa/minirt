#include "../lib/minilibx-linux/mlx.h"
#include "../includes/mlx_mitm.h"
#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"
#include "../includes/obj.h"
#include <stdio.h>

int ray_color(t_ray *ray, t_obj *world)
{
    t_vec3 unit_direction = vec3_unit_vector(&ray->direction);
    double a = 0.5 * (unit_direction.e[1] + 1.0);
    double tzao;

    //atencao ao Tzao negativo
    t_color color;
    tzao = hit_sphere(world, ray);
    if (tzao != -1.0)
        return (0x00FF0000);

    // Sky gradient: white to blue
    t_vec3 white = vec3(1.0, 1.0, 1.0);
    t_vec3 blue = vec3(0.5, 0.7, 1.0);

    t_vec3 white_scaled = vec3_multiply_scalar(&white, 1.0 - a);
    t_vec3 blue_scaled = vec3_multiply_scalar(&blue, a);
    t_vec3 color_vec = vec3_sum(&white_scaled, &blue_scaled);

    color.s_rgba.r = (unsigned char)(255.999 * color_vec.e[0]);
    color.s_rgba.g = (unsigned char)(255.999 * color_vec.e[1]);
    color.s_rgba.b = (unsigned char)(255.999 * color_vec.e[2]);
    color.s_rgba.a = 255;

    return (color.hex);
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

    img.height = 1080;
    img.width = 1080;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.width, img.height, "Hello world!");
    img.img = mlx_new_image(mlx, img.width, img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                &img.endian);
    double wall_width = 7;
    t_vec3 light_source = vec3(0, 0, -5);
    double wall_z = 10;
    double cx;
    double cy;
    t_obj sph;
    sph.pos = vec3(0,0,0);
    sph.data.sphere.radius = 1;

    for (int y = 0; y < img.height; y++)
    {
        cy = wall_width / 2.0 - (wall_width * (double)y / (double)img.height);
        for (int x = 0; x < img.width; x++)
        {
            cx = -(wall_width / 2.0) + (wall_width * (double)x / (double)img.width);
            t_vec3 wall_point = vec3(cx, cy, wall_z);
            t_ray ray;
            ray.origin = light_source;
            t_vec3 dir = vec3_subtract(&wall_point, &ray.origin);
            ray.direction = vec3_multiply_scalar(&dir, 1.0 / vec3_length(&dir));
            my_mlx_pixel_put(&img, x, y, ray_color(&ray, &sph));
        }
    }

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
