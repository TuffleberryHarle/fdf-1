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
