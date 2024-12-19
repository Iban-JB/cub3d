/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:39:19 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/12/17 14:02:17 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "stdio.h"
# include "stdlib.h"
# include "errno.h"
# include <X11/keysym.h>
# include "mlx.h"
# include <fcntl.h>
# include <stdint.h>
# include <math.h>

# define TITLE "cub3D"
# define HEIGHT 720
# define WIDTH 1080
# define TILE_SIZE 8
# define RAYMAX 500
# define FOV 60

# define PINK 16711935
# define RED 16711680
# define BLUE 255
# define GREEN 65280
# define WHITE 0xFFFFFF
# define GRAY 0x808080
# define BLACK 0

# define FORWARD 0
# define BACKWARD 1
# define LEFT 2
# define RIGHT 3
# define MARGIN 2

# define M_PI 3.14159265358979323846
# define RWEST 3.14159265358979323846
# define RSOUTH 4.71238898038
# define RNORTH 1.57079632679
# define REAST 0
# define RADIAN 0.0174533f

typedef struct s_Vector2D
{
	double	x;
	double	y;
}	t_Vector2D;

typedef enum e_bool
{
	true = 1,
	false = 0
}	t_bool;

typedef struct s_grid
{
	int	nb_col;
	int	nb_lin;
	int	len_max;
	int	wid_max;
}	t_grid;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_check_map
{
	t_bool	n;
	t_bool	s;
	t_bool	e;
	t_bool	w;
	t_bool	f;
	t_bool	c;
	t_bool	o;
	t_bool	m;
}	t_check_map;

typedef struct s_color
{
	unsigned long	hex;
	char			**rgb;
	t_bool			complete_color;
}				t_color;

typedef struct s_parse_info
{
	int				nb_line;
	int				len_line;
	char			**file;
	char			**map;
	char			*n;
	char			*s;
	char			*e;
	char			*w;
	t_color			*f;
	t_color			*c;
	t_check_map		check;
}	t_map_info;

typedef struct s_read_file
{
	int		fd;
	char	*tp;
	char	**temp_file;
	char	**final_file;
	t_bool	in_map;
}	t_read_file;

typedef struct s_inputs
{
	t_bool	key_w;
	t_bool	key_s;
	t_bool	key_a;
	t_bool	key_d;
	t_bool	left_arrow;
	t_bool	right_arrow;
}	t_inputs;


typedef struct s_player_info
{
	int			fov;
	double		angle;
	double		speed;
	t_Vector2D	pos;
	t_Vector2D	dir;
	t_Vector2D	plane;
	t_inputs	moves;
}	t_player_info;

typedef struct s_ray2
{
	t_Vector2D	dir;
	t_Vector2D	pos;
	t_Vector2D	prev;
	int			color;
	char		face;
	double		step;
	double		angle;
}	t_ray;

typedef struct s_cube
{
	void			*mlx;
	void			*win;
	t_data			*data;
	t_map_info		*mi;
	t_player_info	*player;
}	t_cube;

t_bool	parse_map(char *path, t_cube *cube);
t_bool	is_map_valid(char **map);
t_bool	init_cube(t_cube *cube);
t_bool	cmp_n_char_after_spaces(char *s1, char *s2, size_t n);
char	*ft_strdup_until_char(const char *s, char c);
char	**tab_join(char **tab, char *str);
char	**tab_dup(char **env);
int		skip_spaces(char *str, size_t i);
void	ft_free_tab(char **arr);
void	free_exit(t_cube *cube);
void	check_file(t_cube *cube);
void	modify_char_in_map(t_cube *cube, char c, char new_c);
void	set_cube_null(t_cube *cube);
void	print_map_info(t_cube *cube);
int		display_cube(t_cube *cube);
int		get_len_max(char **map);
int		get_width_max(char **map);
void	put_pixel(t_cube *cube, unsigned int color, int x, int y);
void	init_player(t_cube *cube);
int		close_window(t_cube *cube);
int		key_press(int keycode, t_cube *cube);
t_bool	validate_file(char *path, char *extension);
void	m_forward(t_cube *cube);
void	m_backward(t_cube *cube);
void	m_right(t_cube *cube);
void	m_left(t_cube *cube);
int		key_release(int keycode, t_cube *cube);
void	handle_moves(t_cube *cube);
void	cast_rays(t_cube *cube);
void    draw_rectangle(t_cube *cube, int x, int y, int color, int size);
void	turn_player(t_cube *cube, int keycode);
void	draw_ray_minimap(t_cube *cube, double angle, double wall_dst);
void	count_len_and_line(char **map, int *len, int *lines);
char	get_face(t_Vector2D hit, int x, int y);
void	find_wall_hit(t_cube *cube, t_ray *ray, t_Vector2D *prev);
void	read_stock_file(char *path, t_cube *cube);
void	find_spawn_player(t_cube *cube);
t_bool	is_empty_line(char *line);

#endif