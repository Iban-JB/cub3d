/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 16:43:45 by ibjean-b          #+#    #+#             */
/*   Updated: 2024-12-18 16:43:45 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/X.h>
#include <X11/keysym.h>

void	init_mlx(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
		free_exit(cube);
	cube->win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, TITLE);
	if (!cube->win)
		free_exit(cube);
	cube->data->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->data->img)
		free_exit(cube);
	cube->data->addr = mlx_get_data_addr(cube->data->img,
			&cube->data->bits_per_pixel, &cube->data->line_length,
			&cube->data->endian);
	if (!cube->data->addr)
		free_exit(cube);
}

void	init_hooks(t_cube *cube)
{
	mlx_hook(cube->win, KeyPress, KeyPressMask, key_press, cube);
	mlx_hook(cube->win, KeyRelease, KeyReleaseMask, key_release, cube);
	mlx_hook(cube->win, DestroyNotify, NoEventMask, close_window, cube);
	mlx_loop_hook(cube->mlx, display_cube, cube);
}

t_bool	init_cube(t_cube *cube)
{
	init_mlx(cube);
	init_hooks(cube);
	init_player(cube);
	return (true);
}

void	set_cube_null(t_cube *cube)
{
	cube->data = ft_calloc(1, sizeof(t_data));
	if (!cube->data)
		free_exit(cube);
	cube->mi = ft_calloc(1, sizeof(t_map_info));
	if (!cube->mi)
		free_exit(cube);
	cube->mi->c = ft_calloc(1, sizeof(t_color));
	if (!cube->mi->c)
		free_exit(cube);
	cube->mi->f = ft_calloc(1, sizeof(t_color));
	if (!cube->mi->f)
		free_exit(cube);
	cube->player = ft_calloc(1, sizeof(t_player_info));
	if (!cube->player)
		free_exit(cube);
	cube->mi->check.c = false;
	cube->mi->check.f = false;
	cube->mi->check.n = false;
	cube->mi->check.s = false;
	cube->mi->check.w = false;
	cube->mi->check.e = false;
	cube->mi->check.m = false;
	cube->mi->c->complete_color = false;
	cube->mi->f->complete_color = false;
	cube->mi->f->complete_color = false;
}

void	init_player(t_cube *cube)
{
	cube->player->moves.key_w = false;
	cube->player->moves.key_s = false;
	cube->player->moves.key_a = false;
	cube->player->moves.key_d = false;
	cube->player->speed = MARGIN;
	cube->player->fov = 60;
	cube->mi->nb_line = get_width_max(cube->mi->map);
	cube->mi->len_line = get_len_max(cube->mi->map);
	find_spawn_player(cube);
}
