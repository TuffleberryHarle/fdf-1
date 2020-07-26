#include "../includes/fdf.h"

void	proj_switch(int key, t_fdf *fdf)
{
    fdf->camera->alpha = 0;
    fdf->camera->beta = 0;
    fdf->camera->gamma = 0;
    if (key == I)
        fdf->camera->projection = ISOMETRIC;
    else if (key == P)
        fdf->camera->projection = PARALLEL;
    drawing(fdf->map, fdf);
}

void	flatten(int key, t_fdf *fdf)
{
    if (key == LESS)
        fdf->camera->z_divisor -= 0.1;
    else if (key == MORE)
        fdf->camera->z_divisor += 0.1;
    if (fdf->camera->z_divisor < 0.1)
        fdf->camera->z_divisor = 0.1;
    else if (fdf->camera->z_divisor > 10)
        fdf->camera->z_divisor = 10;
    drawer(fdf->map, fdf);
}

void	rotate(int key, t_fdf *fdf)
{
    if (key == NUM_2 || key == MAIN_2)
        fdf->camera->alpha += 0.05;
    else if (key == NUM_8 || key == MAIN_8)
        fdf->camera->alpha -= 0.05;
    else if (key == NUM_4 || key == MAIN_4)
        fdf->camera->beta -= 0.05;
    else if (key == NUM_6 || key == MAIN_6)
        fdf->camera->beta += 0.05;
    else if (key == NUM_1 || key == MAIN_1
             || key == NUM_3 || key == MAIN_3)
        fdf->camera->gamma += 0.05;
    else if (key == NUM_7 || key == MAIN_7
             || key == NUM_9 || key == MAIN_9)
        fdf->camera->gamma -= 0.05;
    drawer(fdf->map, fdf);
}

void	move(int key, t_fdf *fdf)
{
    if (key == LEFT)
        fdf->camera->x_offset -= 10;
    else if (key == RIGHT)
        fdf->camera->x_offset += 10;
    else if (key == UP)
        fdf->camera->y_offset -= 10;
    else if (key == DOWN)
        fdf->camera->y_offset += 10;
    drawer(fdf->map, fdf);
}

void	zoom(int key, t_fdf *fdf)
{
    if (key == NUM_PLUS ||
        key == PLUS ||
        key == WHEEL_UP)
        fdf->camera->zoom++;
    else if (key == NUM_MINUS ||
             key == MINUS ||
             key == WHEEL_DOWN)
        fdf->camera->zoom--;
    if (fdf->camera->zoom < 1)
        fdf->camera->zoom = 1;
    drawer(fdf->map, fdf);
}

