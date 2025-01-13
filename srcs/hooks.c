/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:44:47 by ibjean-b          #+#    #+#             */
/*   Updated: 2025/01/13 18:24:24 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/X.h>
#include <X11/keysym.h>

void	handle_moves(t_cube *cube)
{
	if (cube->player->moves.key_w)
		m_forward(cube);
	if (cube->player->moves.key_s)
		m_backward(cube);
	if (cube->player->moves.key_a)
		m_left(cube);
	if (cube->player->moves.key_d)
		m_right(cube);
	if (cube->player->moves.left_arrow)
		turn_player(cube, 0);
	if (cube->player->moves.right_arrow)
		turn_player(cube, 1);
}

int	close_window(t_cube *cube)
{
	free_exit(cube);
	return (0);
}

void	turn_player(t_cube *cube, int dir)
{
	if (!dir)
		cube->player->angle += 0.05;
	else
		cube->player->angle -= 0.05;
	if (cube->player->angle < 0)
		cube->player->angle += 2 * M_PI;
	else if (cube->player->angle > 2 * M_PI)
		cube->player->angle -= 2 * M_PI;
}

int	key_release(int keycode, t_cube *cube)
{
	if (keycode == XK_w)
		cube->player->moves.key_w = false;
	else if (keycode == XK_s)
		cube->player->moves.key_s = false;
	else if (keycode == XK_a)
		cube->player->moves.key_a = false;
	else if (keycode == XK_d)
		cube->player->moves.key_d = false;
	else if (keycode == XK_Left)
		cube->player->moves.left_arrow = false;
	else if (keycode == XK_Right)
		cube->player->moves.right_arrow = false;
	return (0);
}

int	key_press(int keycode, t_cube *cube)
{
	if (keycode == XK_Escape)
		free_exit(cube);
	if (keycode == XK_w)
		cube->player->moves.key_w = true;
	else if (keycode == XK_s)
		cube->player->moves.key_s = true;
	else if (keycode == XK_a)
		cube->player->moves.key_a = true;
	else if (keycode == XK_d)
		cube->player->moves.key_d = true;
	if (keycode == XK_Left)
		cube->player->moves.left_arrow = true;
	if (keycode == XK_Right)
		cube->player->moves.right_arrow = true;
	return (0);
}
