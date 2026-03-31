//
// Created by afonsusousa on 11/9/25.
//

#ifndef MINIRT_MLX_MITM_H
#define MINIRT_MLX_MITM_H

typedef struct	s_data {
    void	*img;
    char	*addr;
    int     height;
    int     width;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}				t_data;


#endif //MINIRT_MLX_MITM_H