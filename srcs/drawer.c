#include "../includes/fdf.h"

void	options_displayer(t_fdf *fdf)
{
    int		y;
    void	*mlx;
    void	*win;

    y = 0;
    mlx = fdf->mlx;
    win = fdf->win;
    mlx_string_put(mlx, win, 65, y += 20, TEXT_COLOR, "How to Use");
    mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "Zoom: Scroll or +/-");
    mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Move: Arrows");
    mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Flatten: </>");
    mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate: Press & Move");
    mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate:");
    mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "X-Axis - 2/8");
    mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Y-Axis - 4/6");
    mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Z-Axis - 1(3)/7(9)");
    mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Projection");
    mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "ISO: I Key");
    mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Parallel: P Key");
}

static void	trace_drawing(t_point f, t_point s, t_fdf *fdf)
{
    t_point	diff;
    t_point	sign;
    t_point	cur;
    int		error[2];

	diff.x = FT_ABS(s.x - f.x);
	diff.y = FT_ABS(s.y - f.y);
    sign.x = (f.x < s.x) ? 1 : -1;
    sign.y = (f.y < s.y) ? 1 : -1;
    error[0] = diff.x - diff.y;
    cur = f;
    while (cur.x != s.x || cur.y != s.y)
    {
		dot_putting(fdf, cur.x, cur.y, color_getting(cur, f, s, diff));
        if ((error[1] = error[0] * 2) > -diff.y)
        {
            error[0] -= diff.y;
            cur.x += sign.x;
        }
        if (error[1] < diff.x)
        {
            error[0] += diff.x;
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
    options_displayer(fdf);
}