/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:55:59 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/14 21:44:56 by amagno-r         ###   ########.fr       */
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
#include "../includes/render.h"
#include <stdio.h>
#include <string.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (data->height <= y || y < 0)
		return ;
	dst = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_world		w __attribute__((aligned(32)));
	t_color		p_col;
	t_ray		r;
	int			cx, cy, x, y, s;
	bool		is_pretty = false;

	if (argc < 2)
	{
		printf("Usage: ./minirt <map.3d> [--pretty]\n");
		return (1);
	}
	if (argc >= 3 && strcmp(argv[2], "--pretty") == 0)
		is_pretty = true;

	parse_file(&w, argv[1]);
	init_camera(&w.camera, 1920, 16.0 / 9.0);

	if (!is_pretty) {
		w.camera.samples_per_pixel = 1;
		w.camera.pixel_samples_scale = 1.0;
	}

	img.width = w.camera.image_width;
	img.height = w.camera.image_height;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, img.width, img.height, "Hello");
	img.img = mlx_new_image(mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
					&img.line_length, &img.endian);

	for (cy = 0; cy * 16 < img.height; cy++)
	{
		for (cx = 0; cx * 16 < img.width; cx++)
		{
			for (y = 0; y < 16; y++)
			{
				for (x = 0; x < 16; x++)
				{
					if (cx * 16 + x >= img.width || cy * 16 + y >= img.height)
						continue ;
					p_col = vec3(0, 0, 0);
					for (s = 0; s < w.camera.samples_per_pixel; s++)
					{
						r = get_ray(&w.camera, cx * 16 + x, cy * 16 + y);
						p_col = v3_add(p_col, phong_ray_color(&r, &w));
					}
					p_col = v3_muls(p_col, w.camera.pixel_samples_scale);
					my_mlx_pixel_put(&img, cx * 16 + x, cy * 16 + y, color_to_int(p_col));
				}
			}
		}
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_do_sync(mlx);
	}
	mlx_loop(mlx);
}
