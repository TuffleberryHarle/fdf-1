#include "../includes/fdf.h"

static void			arr_freer(char **arr)
{
    size_t i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

static t_coord_val	*new_coord(char *s)
{
    t_coord_val	*coord;
    char		**pieces;

    if (!(coord = (t_coord_val *)ft_memalloc(sizeof(t_coord_val))))
        terminator(ERR_MAP_READING);
    if (!(pieces = ft_strsplit(s, ',')))
        terminator(ERR_MAP_READING);
    if (!ft_isnumber(pieces[0], 10))
        terminator(ERR_MAP_READING);
    if (pieces[1] && !ft_isnumber(pieces[1], 16))
        terminator(ERR_MAP_READING);
    coord->z = ft_atoi(pieces[0]);
    coord->color = pieces[1] ? ft_atoi_base(pieces[1], 16) : -1;
    coord->next = NULL;
    arr_freer(pieces);
    return (coord);
}

static void			line_parser(char **coords_line,
                                   t_coord_val **coords_stack,
                                   t_map *map)
{
    int	width;

    width = 0;
    while (*coords_line)
    {
        push(coords_stack, new_coord(*(coords_line++)));
        width++;
    }
    if (map->height == 0)
        map->width = width;
    else if (map->width != width)
        terminator(ERR_MAP);
}

int					map_reader(const int fd,
                                  t_coord_val **coords_stack,
                                  t_map *map)
{
    char	*line;
    char	**coords_line;
    int		result;

    while ((result = get_next_line(fd, &line)) == 1)
    {
        if (!(coords_line = ft_strsplit(line, ' ')))
            terminator(ERR_MAP_READING);
        line_parser(coords_line, coords_stack, map);
        arr_freer(coords_line);
        ft_strdel(&line);
        map->height++;
    }
    if (!(*coords_stack))
        terminator(ERR_MAP);
    return (result);
}