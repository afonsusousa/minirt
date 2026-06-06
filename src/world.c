/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2026/06/06 12:00:00 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/world.h"
#include "../includes/mlx_mitm.h"
#include "../lib/minilibx-linux/mlx.h"
#include <stdlib.h>

bool	destroy_world(t_world *wrld)
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
		mlx_destroy_window(ctx->mlx, ctx->mlx_win);
	if (ctx->mlx && ctx->img.img_ptr)
		mlx_destroy_image(ctx->mlx, ctx->img.img_ptr);
	if (ctx->mlx)
		mlx_destroy_display(ctx->mlx);
	if (ctx->mlx)
		free(ctx->mlx);
	if (ctx->w)
		destroy_world(ctx->w);
	ctx->w = NULL;
	ctx->mlx_win = NULL;
	ctx->img.img_ptr = NULL;
	exit(0);
}
