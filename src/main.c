#include "../lib/minilibx-linux/mlx.h"
#include "../includes/mlx_mitm.h"
#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"


t_color ray_color(const t_ray *ray)
{
    t_vec3 unit_direction = vec3_unit_vector(&ray->direction);
    double a = 0.5 * (unit_direction.e[1] + 1.0);

    // Sky gradient: white to blue
    t_vec3 white = vec3(1.0, 1.0, 1.0);
    t_vec3 blue = vec3(0.5, 0.7, 1.0);

    t_vec3 white_scaled = vec3_multiply_scalar(&white, 1.0 - a);
    t_vec3 blue_scaled = vec3_multiply_scalar(&blue, a);
    t_vec3 color_vec = vec3_sum(&white_scaled, &blue_scaled);

    t_color color;
    color.s_rgba.r = (unsigned char)(255.999 * color_vec.e[0]);
    color.s_rgba.g = (unsigned char)(255.999 * color_vec.e[1]);
    color.s_rgba.b = (unsigned char)(255.999 * color_vec.e[2]);
    color.s_rgba.a = 255;

    return (color);
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
    img.width = 1920;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.width, img.height, "Hello world!");
    img.img = mlx_new_image(mlx, img.width, img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                &img.endian);

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1920;

    int image_height = (int) (image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width / (double)image_height);
    t_point camera_center = vec3(0, 0, 0);

    // across the horizontal and down the vertical viewport edges
    t_vec3 viewport_u = vec3(viewport_width, 0, 0);
    t_vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    t_vec3 pixel_delta_u = vec3_divide(&viewport_u, image_width);
    t_vec3 pixel_delta_v = vec3_divide(&viewport_v, image_height);

    // Calculate the location of the upper left pixel.
    t_vec3 focal_vec = vec3(0, 0, focal_length);
    t_vec3 viewport_half_u = vec3_multiply_scalar(&viewport_u, 0.5);
    t_vec3 viewport_half_v = vec3_multiply_scalar(&viewport_v, 0.5);

    t_vec3 temp1 = vec3_subtract(&camera_center, &focal_vec);
    t_vec3 temp2 = vec3_subtract(&temp1, &viewport_half_u);
    t_vec3 viewport_upper_left = vec3_subtract(&temp2, &viewport_half_v);

    t_vec3 delta_sum = vec3_sum(&pixel_delta_u, &pixel_delta_v);
    t_vec3 delta_half = vec3_multiply_scalar(&delta_sum, 0.5);
    t_vec3 pixel00_loc = vec3_sum(&viewport_upper_left, &delta_half);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            t_vec3 u_offset = vec3_multiply_scalar(&pixel_delta_u, i);
            t_vec3 v_offset = vec3_multiply_scalar(&pixel_delta_v, j);
            t_vec3 temp_center = vec3_sum(&pixel00_loc, &u_offset);
            t_vec3 pixel_center = vec3_sum(&temp_center, &v_offset);

            t_vec3 ray_direction = vec3_subtract(&pixel_center, &camera_center);
            t_ray r;
            r.origin = camera_center;
            r.direction = ray_direction;

            t_color pixel_color = ray_color(&r);
            my_mlx_pixel_put(&img, i, j, pixel_color.hex);
        }
    }

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
