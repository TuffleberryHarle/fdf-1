/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: releanor <releanor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 22:53:04 by releanor          #+#    #+#             */
/*   Updated: 2020/06/27 23:25:55 by releanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		main(int argc, char **argv) {

    int fd;
    t_map *map;
    t_fdf *fdf;
    t_coord_val *coords_stack;

    coords_stack = NULL;
    errno = 0;
    if (argc == 2)
    {
        if ((fd = open(argv[1],O_RDONLY) < 0))
            terminator(ERR_MAP);
        map = map_initializer();
        if (map_reader(fd, &coords_stack, map) == -1)
            terminator(ERR_MAP_READING);
        fdf = fdf_initializer(map);
        stack_to_arrays(&coords_stack, map);
        fdf->camera = camera_initializer(fdf);
        drawer(fdf->map, fdf);
    }
    return (0);
}