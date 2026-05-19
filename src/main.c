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
#include "../includes/mlx_mitm.h"
#include "../includes/obj.h"
#include "../includes/ray.h"
#include "../includes/render.h"
#include "../includes/vec3.h"
#include "../lib/minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"

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

static int	render_loop(void *arg)
{
	t_mlx_context	*ctx;
	int				cx;
	int				cy;
	static bool		rendered = false;

	ctx = (t_mlx_context *)arg;
	if (!ctx || !ctx->w || rendered)
		return (0);
	cy = 0;
	while (cy < ctx->img.height)
	{
		cx = 0;
		while (cx < ctx->img.width)
		{
			render_pixel(ctx->w, &ctx->img, cx, cy);
			cx++;
		}
		cy++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, ctx->img.img_ptr, 0, 0);
	rendered = true;
	return (0);
}

static void	setup_window(t_mlx_context *ctx, int width, int height)
{
	ctx->mlx = mlx_init();
	ctx->mlx_win = mlx_new_window(ctx->mlx, width, height, "minirt");
	ctx->img.width = width;
	ctx->img.height = height;
	ctx->img.img_ptr = mlx_new_image(ctx->mlx, width, height);
	ctx->img.addr = mlx_get_data_addr(ctx->img.img_ptr,
			&ctx->img.bits_per_pixel,
			&ctx->img.line_length,
			&ctx->img.endian);
}

static bool	destroy_world(t_world *wrld)
{
	if (!wrld)
		return (true);
	if (wrld->objects)
	{
		free(wrld->objects);
		wrld->objects = NULL;
	}
	if (wrld->lights)
	{
		free(wrld->lights);
		wrld->lights = NULL;
	}
	wrld->has_ambient = false;
	return (true);
}

int	close_window(void *arg)
{
	t_mlx_context	*ctx;

	ctx = (t_mlx_context *)arg;
	if (!ctx)
		exit(1);
	if (ctx->mlx)
		mlx_loop_hook(ctx->mlx, NULL, NULL);
	if (ctx->mlx && ctx->mlx_win)
	{
		mlx_destroy_window(ctx->mlx, ctx->mlx_win);
		ctx->mlx_win = NULL;
	}
	if (ctx->mlx && ctx->img.img_ptr)
	{
		mlx_destroy_image(ctx->mlx, ctx->img.img_ptr);
		ctx->img.img_ptr = NULL;
	}
	if (ctx->mlx)
		mlx_destroy_display(ctx->mlx);
	if (ctx->mlx)
		free(ctx->mlx);
	if (ctx->w)
	{
		destroy_world(ctx->w);
		ctx->w = NULL;
	}
	exit(0);
}

int	handle_input(int key, void *arg)
{
	t_mlx_context	*ctx;

	ctx = (t_mlx_context *)arg;
	if (key == 65307 || key == 53)
		close_window(ctx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx_context	ctx;
	t_world			w;

	if (argc < 2)
	{
		printf("Usage: ./minirt <map.3d>\n");
		return (1);
	}
	w.objects = NULL;
	w.lights = NULL;
	if (parse_file(&w, argv[1]))
		return (destroy_world(&w));
	ctx.w = &w;
	init_camera(&w.camera, 1920, 16.0 / 9.0);
	setup_window(&ctx, w.camera.image_width, w.camera.image_height);
	mlx_hook(ctx.mlx_win, 2, 1L << 0, &handle_input, &ctx);
	mlx_hook(ctx.mlx_win, 17, 1L << 0, &close_window, &ctx);
	mlx_loop_hook(ctx.mlx, &render_loop, &ctx);
	mlx_loop(ctx.mlx);
	return (0);
}