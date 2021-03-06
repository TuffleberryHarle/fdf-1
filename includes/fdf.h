/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: releanor <releanor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 22:53:04 by releanor          #+#    #+#             */
/*   Updated: 2020/06/27 23:25:55 by releanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

#include "err_msg.h"
#include "libft.h"
#include "mlx.h"
#include "colors.h"
#include "keys.h"
#include "math.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct			s_point
{
    int					x;
    int					y;
    int					z;
    int					color;
}						t_point;

typedef enum
{
    false,
    true
}	t_bool;

typedef struct			s_map
{
    int					width;
    int					height;
    int					*coords_arr;
    int					*colors_arr;
    int					z_min;
    int					z_max;
    int					z_range;
}						t_map;

typedef struct			s_coord_val
{
    int					z;
    int					color;
    struct s_coord_val	*next;
}						t_coord_val;

typedef struct			s_mouse
{
    char				is_pressed;
    int					x;
    int					y;
    int					previous_x;
    int					previous_y;
}						t_mouse;

typedef enum
{
    ISOMETRIC,
    PARALLEL
}	t_projection;

typedef struct			s_camera
{
    t_projection		projection;
    int					zoom;
    double				alpha;
    double				beta;
    double				gamma;
    float				z_divisor;
    int					x_offset;
    int					y_offset;
}						t_camera;

/*
 * mlx_ptr for the connection to the display
 * win_ptr the window to use
 * img_ptr the image
 * mlx_get_data_addr() returns information about the created image, allowing a user to modify it later
 * bits_per_pixel will be filled with the number of bits needed to represent a pixel color (also called the depth of the image)
 * line_size is the number of bytes used to store one line of the image in memory. This information is needed to move from one line to another in the image
 * endian tells you whether the pixel color in the image needs to be stored in little endian (endian == 0), or big endian (endian == 1)
 */
typedef struct			s_fdf
{
    void				*mlx;
    void				*win;
    void				*img;
    char				*data_addr;
    int					bits_per_pixel;
    int					line_size;
    int					endian;
    t_camera			*camera;
    t_map				*map;
    t_mouse				*mouse;
}						t_fdf;

# define WIN_WIDTH  1024
# define WIN_HEIGHT 720
# define MENU_WIDTH 250
# define MASK 0xFF
# define SHIFT_RED 16
# define SHIFT_GREEN 8
# define FT_MIN(A, B) (((A) < (B)) ? (A) : (B))
# define FT_MAX(A, B) (((A) > (B)) ? (A) : (B))

# define FT_ABS(X) (((X) < 0) ? (-(X)) : (X))

# define FT_UINT_MAX	((unsigned)(~0L))
# define FT_INT_MAX		((int)(FT_UINT_MAX >> 1))
# define FT_INT_MIN		((int)(~FT_INT_MAX))

void	terminator(char *s);
t_map		*map_initializer(void);
int					map_reader(const int fd, t_coord_val **coords_stack, t_map *map);
static void			line_parser(char **coords_line, t_coord_val **coords_stack, t_map *map);
void		push(t_coord_val **coords_stack, t_coord_val *new);
t_coord_val	*pop(t_coord_val **coords_stack);
t_bool				ft_isnumber(char *str, int base);
int					ft_atoi_base(const char *str, int base);
t_fdf		*fdf_initializer(t_map *map);
void		stack_to_arrays(t_coord_val **coords_stack, t_map *map);
t_camera	*camera_initializer(t_fdf *fdf);
void		drawer(t_map *map, t_fdf *fdf);
t_point		projector(t_point p, t_fdf *fdf);
t_point	point_creator(int x, int y, t_map *map);
int	color_setting(int z, t_map *map);
double	determ(int start, int end, int curr);
void	key_handler(t_fdf *fdf);
void	zoom(int key, t_fdf *fdf);
void	move(int key, t_fdf *fdf);
void	rotate(int key, t_fdf *fdf);
void	flatten(int key, t_fdf *fdf);
void	proj_switch(int key, t_fdf *fdf);
int			mouse_down(int button, int x, int y, void *param);
int			mouse_up(int button, int x, int y, void *param);
int			mouse_moving(int x, int y, void *param);
static void	dot_putting(t_fdf *fdf, int x, int y, int color);
int	color_getting(t_point cur, t_point start, t_point end, t_point diff);

#endif