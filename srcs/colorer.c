#include "../includes/fdf.h"

int	color_setting(int z, t_map *map)
{
	double	val;

	val = determ(map->z_min, map->z_max, z);
	if (val < 0.2)
		return (COLOR_DISCO);
	else if (val < 0.4)
		return (COLOR_BRICK_RED);
	else if (val < 0.6)
		return (COLOR_FLAMINGO);
	else if (val < 0.8)
		return (COLOR_JAFFA);
	else
		return (COLOR_SAFFRON);
}

int	shade_getting(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	color_getting(t_point cur, t_point start, t_point end, t_point diff)
{
	int		red;
	int		green;
	int		blue;
	double	clr_prcnt;

	if (cur.color == end.color)
		return (cur.color);
	if (diff.x > diff.y)
		clr_prcnt = determ(start.x, end.x, cur.x);
	else
		clr_prcnt = determ(start.y, end.y, cur.y);
	red = shade_getting((start.color >> SHIFT_RED) & MASK,
						(end.color >> SHIFT_RED) & MASK,
						clr_prcnt);
	green = shade_getting((start.color >> SHIFT_GREEN) & MASK,
						  (end.color >> SHIFT_GREEN) & MASK,
						  clr_prcnt);
	blue = shade_getting(start.color & MASK,
						 end.color & MASK,
						 clr_prcnt);
	return ((red << SHIFT_RED) | (green << SHIFT_GREEN) | blue);
}