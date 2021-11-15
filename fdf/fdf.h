#ifndef FDF_H
#define FDF_H

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilibx_macos/mlx.h"
#include <fcntl.h>
#include <stdio.h>

#define SCALE 20

typedef struct s_fdf
{
    void    *mlx;
    void    *win;
    int     width;
    int     height;
    int     color;
    int     **matrice;
}t_fdf;


#endif
