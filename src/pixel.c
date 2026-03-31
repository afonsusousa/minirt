//
// Created by afonsusousa on 11/9/25.
//

#include "../includes/color.h"
#include "../includes/mlx_mitm.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
        return ;
    if (!data || !data->addr)
        return ;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void	draw_pixel_color(t_data *data, int x, int y, t_color *color)
{
    if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
        return ;
    if (!data || !color)
        return ;
    if (color->s_rgba.a == 255)
        return (my_mlx_pixel_put(data, x, y, color->hex & 0xFFFFFF));
    if (color->s_rgba.a == 0)
        return ;
    my_mlx_pixel_put(data, x, y, color->hex);
}