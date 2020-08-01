#include "../includes/fdf.h"

static void	dot_putting(t_fdf *fdf, int x, int y, int color)
{
	int		i;

	if (x >= MENU_WIDTH && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->line_size);
		fdf->data_addr[i++] = color;
		fdf->data_addr[i++] = color >> SHIFT_GREEN;
		fdf->data_addr[i] = color >> SHIFT_RED;
	}
}

double	determ(int start, int end, int curr)
{
	double	location;
	double	gap;

	location = curr - start;
	gap = end - start;
	return ((gap == 0) ? 1.0 : (location / gap));
}

int		index_getter(int x, int y, int width)
{
	return (y * width + x);
}

t_point	point_creator(int x, int y, t_map *map)
{
    t_point	point;
    int		index;

    index = index_getter(x, y, map->width);
    point.x = x;
    point.y = y;
    point.z = map->coords_arr[index];
    point.color = (map->colors_arr[index] == -1) ?
				  color_setting(point.z, map) : map->colors_arr[index];
    return (point);
}

void		stack_to_arrays(t_coord_val **coords_stack, t_map *map)
{
    t_coord_val	*coord;
    ssize_t		i;
    size_t		arr_size;

    arr_size = map->width * map->height * sizeof(int);
    if (!(map->coords_arr = (int *)ft_memalloc(arr_size)))
        terminator(ERR_CONV_TO_ARR);
    if (!(map->colors_arr = (int *)ft_memalloc(arr_size)))
        terminator(ERR_CONV_TO_ARR);
    i = map->width * map->height - 1;
    while ((coord = pop(coords_stack)) && i >= 0)
    {
        map->coords_arr[i] = coord->z;
        map->colors_arr[i] = coord->color;
        if (coord->z > map->z_max)
            map->z_max = coord->z;
        if (coord->z < map->z_min)
            map->z_min = coord->z;
        i--;
        free(coord);
    }
    map->z_range = map->z_max - map->z_min;
}
