//
// Created by afonsusousa on 11/9/25.
//

#ifndef MINIRT_COLOR_H
#define MINIRT_COLOR_H

typedef union u_color
{
    int				hex;
    struct
    {
        unsigned char	b;
        unsigned char	g;
        unsigned char	r;
        unsigned char	a;
    }	s_rgba;
}					t_color;

#endif //MINIRT_COLOR_H