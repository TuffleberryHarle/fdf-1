#include "../includes/fdf.h"

t_map		*map_initializer(void)
{
    t_map	*map;

    if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
        terminator(ERR_MAP_INIT);
    map->width = 0;
    map->height = 0;
    map->coords_arr = NULL;
    map->colors_arr = NULL;
    map->z_min = FT_INT_MAX;
    map->z_max = FT_INT_MIN;
    map->z_range = 0;
    return (map);
}

t_fdf		*fdf_initializer(t_map *map)
{
    t_fdf	*fdf;

    if (!(fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
        terminator(ERR_FDF_INIT);
    if (!(fdf->mlx = mlx_init()))
        terminator(ERR_FDF_INIT);
    if (!(fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FDF ting")))
        terminator(ERR_FDF_INIT);
    if (!(fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT)))
        terminator(ERR_FDF_INIT);
    fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
									   &(fdf->line_size), &(fdf->endian));
    fdf->map = map;
    if (!(fdf->mouse = (t_mouse *)ft_memalloc(sizeof(t_mouse))))
        terminator(ERR_FDF_INIT);
    return (fdf);
}

t_camera	*camera_initializer(t_fdf *fdf)
{
    t_camera	*camera;

    if (!(camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
        terminator(ERR_CAMERA_INIT);
    camera->zoom = FT_MIN((WIN_WIDTH - MENU_WIDTH) / fdf->map->width / 2,
                          WIN_HEIGHT / fdf->map->height / 2);
    camera->alpha = 0;
    camera->beta = 0;
    camera->gamma = 0;
    camera->z_divisor = 1;
    camera->x_offset = 0;
    camera->y_offset = 0;
    return (camera);
}