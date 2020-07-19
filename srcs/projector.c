#include "../includes/fdf.h"

static void	isometric(int *x, int *y, int z)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

static void	x_rotating(int *y, int *z, double alpha)
{
	int prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

static void	y_rotating(int *x, int *z, double beta)
{
	int prev_x;

	prev_x = *x;
	*x = prev_x * cos(beta) + *z * sin(beta);
	*z = -prev_x * sin(beta) + *z * cos(beta);
}

static void	z_rotating(int *x, int *y, double gamma)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(gamma) - prev_y * sin(gamma);
	*y = prev_x * sin(gamma) + prev_y * cos(gamma);
}

t_point		projector(t_point p, t_fdf *fdf)
{
    p.x *= fdf->camera->zoom;
    p.y *= fdf->camera->zoom;
    p.z *= fdf->camera->zoom / fdf->camera->z_divisor;
    p.x -= (fdf->map->width * fdf->camera->zoom) / 2;
    p.y -= (fdf->map->height * fdf->camera->zoom) / 2;
	x_rotating(&p.y, &p.z, fdf->camera->alpha);
	y_rotating(&p.x, &p.z, fdf->camera->beta);
	z_rotating(&p.x, &p.y, fdf->camera->gamma);
    if (fdf->camera->projection == ISOMETRIC)
		isometric(&p.x, &p.y, p.z);
    p.x += (WIN_WIDTH - MENU_WIDTH) / 2 + fdf->camera->x_offset + MENU_WIDTH;
    p.y += (WIN_HEIGHT + fdf->map->height * fdf->camera->zoom) / 2
           + fdf->camera->y_offset;
    return (p);
}