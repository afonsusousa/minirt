/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:55:59 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 19:40:00 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"
#include "../includes/color.h"
#include "../includes/intersection.h"
#include "../includes/interval.h"
#include "../includes/mlx_mitm.h"
#include "../includes/obj.h"
#include "../includes/ray.h"
#include "../includes/render.h"
#include "../includes/vec3.h"
#include "../includes/world.h"
#include "../lib/minilibx-linux/mlx.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (data->height <= y || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	render_pixel(t_world *w, t_data *img, int px, int py)
{
	t_ray	r;
	t_color	p_col;
	int		s;

	p_col = vec3(0, 0, 0);
	s = 0;
	while (s < w->camera.samples_per_pixel)
	{
		r = get_ray(&w->camera, px, py);
		p_col = v3_add(p_col, phong_ray_color(&r, w));
		s++;
	}
	p_col = v3_muls(p_col, w->camera.pixel_samples_scale);
	my_mlx_pixel_put(img, px, py, color_to_int(p_col));
}

static void	render_chunk(t_world *w, t_data *img, int cx, int cy)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = 0;
	while (y < 16)
	{
		x = 0;
		while (x < 16)
		{
			px = cx * 16 + x;
			py = cy * 16 + y;
			if (px >= img->width || py >= img->height)
			{
				x++;
				continue ;
			}
			render_pixel(w, img, px, py);
			x++;
		}
		y++;
	}
}

static void	render_loop(t_world *w, t_data *img, void *mlx, void *mlx_win)
{
	int	cx;
	int	cy;

	cy = 0;
	while (cy * 16 < img->height)
	{
		cx = 0;
		while (cx * 16 < img->width)
		{
			render_chunk(w, img, cx, cy);
			cx++;
		}
		mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
		mlx_do_sync(mlx);
		cy++;
	}
}

static void	setup_window(t_data *img, void **mlx, void **win)
{
	*mlx = mlx_init();
	*win = mlx_new_window(*mlx, img->width, img->height, "minirt");
	img->img = mlx_new_image(*mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

int	main(int argc, char **argv)
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;

	t_world w __attribute__((aligned(32)));
	if (argc < 2)
	{
		printf("Usage: ./minirt <map.3d>\n");
		return (1);
	}
	parse_file(&w, argv[1]);
	init_camera(&w.camera, 1920, 16.0 / 9.0);
	img.width = w.camera.image_width;
	img.height = w.camera.image_height;
	setup_window(&img, &mlx, &mlx_win);
	render_loop(&w, &img, mlx, mlx_win);
	mlx_loop(mlx);
	return (0);
}
