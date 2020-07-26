#include "../includes/fdf.h"

int			mouse_moving(int x, int y, void *param)
{
    t_fdf	*fdf;

    fdf = (t_fdf *)param;
    fdf->mouse->previous_x = fdf->mouse->x;
    fdf->mouse->previous_y = fdf->mouse->y;
    fdf->mouse->x = x;
    fdf->mouse->y = y;
    if (fdf->mouse->is_pressed)
    {
        fdf->camera->beta += (x - fdf->mouse->previous_x) * 0.002;
        fdf->camera->alpha += (y - fdf->mouse->previous_y) * 0.002;
        drawer(fdf->map, fdf);
    }
    return (0);
}

int			mouse_up(int button, int x, int y, void *param)
{
    t_fdf	*fdf;

    (void)x;
    (void)y;
    (void)button;
    fdf = (t_fdf *)param;
    fdf->mouse->is_pressed = false;
    return (0);
}

int			mouse_down(int button, int x, int y, void *param)
{
    t_fdf	*fdf;

    (void)x;
    (void)y;
    fdf = (t_fdf *)param;
    if (button == WHEEL_UP || button == WHEEL_DOWN)
        zoom(button, fdf);
    else if (button == MOUSE_LEFT)
        fdf->mouse->is_pressed = true;
    return (0);
}
