/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:44:47 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/11/20 15:31:04 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/keysym.h>
#include <X11/X.h>

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
