#include "../includes/fdf.h"

int			key_down(int key, void *param)
{
    t_fdf	*fdf;

    fdf = (t_fdf *)param;
    if (key == ESC)
        exit(0);
    if (key == NUM_PLUS || key == PLUS
        || key == NUM_MINUS || key == MINUS)
        zoom(key, fdf);
    else if (key == LEFT || key == RIGHT
             || key == UP || key == DOWN)
        move(key, fdf);
    else if (key == NUM_1 || key == MAIN_1
             || key == NUM_2 || key == MAIN_2
             || key == NUM_3 || key == MAIN_3
             || key == NUM_4 || key == MAIN_4
             || key == NUM_6 || key == MAIN_6
             || key == NUM_7 || key == MAIN_7
             || key == NUM_8 || key == MAIN_8
             || key == NUM_9 || key == MAIN_9)
        rotate(key, fdf);
    else if (key == LESS || key == MORE)
        flatten(key, fdf);
    else if (key == P || key == I)
        proj_switch(key, fdf);
    return (0);
}

int		close_n_exit(void *param)
{
    (void)param;
    exit(0);
}

void	key_handler(t_fdf *fdf)
{
    mlx_hook(fdf->win, 17, 0, close_n_exit, fdf);
    mlx_hook(fdf->win, 2, 0, key_down, fdf);
    mlx_hook(fdf->win, 4, 0, mouse_down, fdf);
    mlx_hook(fdf->win, 5, 0, mouse_up, fdf);
    mlx_hook(fdf->win, 6, 0, mouse_moving, fdf);
}
