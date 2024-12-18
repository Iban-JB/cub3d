/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:33:53 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/12/16 19:06:05 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_bool	is_wall(t_cube *cube, double y, double x, int flag)
{
	t_Vector2D	dir;
	t_Vector2D	margin;

	dir.x = sin(-cube->player->angle);
	dir.y = cos(cube->player->angle);
	if (dir.x < 0)
		margin.x = -2;
	else
		margin.x = 2;
	if (dir.y < 0)
		margin.y = -2;
	else
		margin.y = 2;
	if (flag == 1 || flag == 2)
	{
		margin.x *= -1;
		margin.y *= -1;
	}
	if (cube->mi->map[(int)(x + margin.x) / TILE_SIZE][(int)(y + margin.y)
		/ TILE_SIZE] && cube->mi->map[(int)(x + margin.x) / TILE_SIZE][(int)(y
			+ margin.y) / TILE_SIZE] && x >= 0 && y >= 0
		&& cube->mi->map[(int)(x + margin.x) / TILE_SIZE][(int)(y + margin.y)
		/ TILE_SIZE] == '1')
		return (true);
	return (false);
}

void	m_forward(t_cube *cube)
{
	double	new_y;
	double	new_x;

	new_x = cube->player->pos.x + cos(cube->player->angle)
		* cube->player->speed;
	new_y = cube->player->pos.y - sin(cube->player->angle)
		* cube->player->speed;
	if (!is_wall(cube, new_x, new_y, 0))
	{
		cube->player->pos.x = new_x;
		cube->player->pos.y = new_y;
	}
}

void	m_backward(t_cube *cube)
{
	double	new_y;
	double	new_x;

	new_x = cube->player->pos.x - cos(cube->player->angle)
		* cube->player->speed;
	new_y = cube->player->pos.y + sin(cube->player->angle)
		* cube->player->speed;
	if (!is_wall(cube, new_x, new_y, 1))
	{
		cube->player->pos.x = new_x;
		cube->player->pos.y = new_y;
	}
}

void	m_right(t_cube *cube)
{
	double	new_x;
	double	new_y;

	new_x = cube->player->pos.x + sin(cube->player->angle)
		* cube->player->speed;
	new_y = cube->player->pos.y + cos(cube->player->angle)
		* cube->player->speed;
	if (!is_wall(cube, new_x, new_y, 0))
	{
		cube->player->pos.x = new_x;
		cube->player->pos.y = new_y;
	}
}

void	m_left(t_cube *cube)
{
	double	new_x;
	double	new_y;

	new_x = cube->player->pos.x - sin(cube->player->angle)
		* cube->player->speed;
	new_y = cube->player->pos.y - cos(cube->player->angle)
		* cube->player->speed;
	if (!is_wall(cube, new_x, new_y, 2))
	{
		cube->player->pos.x = new_x;
		cube->player->pos.y = new_y;
	}
}
