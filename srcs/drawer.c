#include "../includes/fdf.h"

static void	trace_drawing(t_point f, t_point s, t_fdf *fdf)
{
    t_point	delta;
    t_point	sign;
    t_point	cur;
    int		error[2];

    delta.x = FT_ABS(s.x - f.x);
    delta.y = FT_ABS(s.y - f.y);
    sign.x = f.x < s.x ? 1 : -1;
    sign.y = f.y < s.y ? 1 : -1;
    error[0] = delta.x - delta.y;
    cur = f;
    while (cur.x != s.x || cur.y != s.y)
    {
        put_pixel(fdf, cur.x, cur.y, get_color(cur, f, s, delta));
        if ((error[1] = error[0] * 2) > -delta.y)
        {
            error[0] -= delta.y;
            cur.x += sign.x;
        }
        if (error[1] < delta.x)
        {
            error[0] += delta.x;
            cur.y += sign.y;
        }
    }
}

static void	background_drawing(t_fdf *fdf)
{
    int	*field;
    int	i;

    ft_bzero(fdf->data_addr,
             WIN_WIDTH * WIN_HEIGHT * (fdf->bits_per_pixel / 8));
    field = (int *)(fdf->data_addr);
    i = 0;
    while (i < WIN_HEIGHT * WIN_WIDTH)
    {
        field[i] = (i % WIN_WIDTH < MENU_WIDTH) ? MENU_BCKGRND : BCKGRND;
        i++;
    }
}

void		drawer(t_map *map, t_fdf *fdf)
{
    int		x;
    int		y;

    background_drawing(fdf);
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (x != fdf->map->width - 1)
                trace_drawing(projector(point_creator(x, y, map), fdf),
							  projector(point_creator(x + 1, y, map), fdf), fdf);
            if (y != fdf->map->height - 1)
                trace_drawing(projector(point_creator(x, y, map), fdf),
							  projector(point_creator(x, y + 1, map), fdf), fdf);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
    print_menu(fdf);
}