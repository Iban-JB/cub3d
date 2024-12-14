/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-02 12:33:53 by ibjean-b          #+#    #+#             */
/*   Updated: 2024-12-02 12:33:53 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

t_bool	is_wall(t_cube *cube, int y, int x)
{
	printf("x = %d, y = %d, c = %c\n", x, y, cube->mi->map[x][y]);
	if (cube->mi->map[x] && cube->mi->map[x][y] && x > 0 && y > 0 && cube->mi->map[x][y] == '1')
		return (true);
	return (false);
}

void	m_forward(t_cube *cube)
{
	double	new_y;
	double	new_x;

	new_x = cube->player->pos.x + cos(cube->player->angle) * cube->player->speed; 
	new_y = cube->player->pos.y - sin(cube->player->angle) * cube->player->speed;	
	if (!is_wall(cube, (int)(new_x / TILE_SIZE), (int)(new_y/ TILE_SIZE)))
	{	
		cube->player->pos.x = new_x;
		cube->player->pos.y = new_y;
	}
}

void	m_backward(t_cube *cube)
{
	double	new_y;
	double	new_x;

	new_x = cube->player->pos.x - cos(cube->player->angle) * cube->player->speed; 
	new_y = cube->player->pos.y + sin(cube->player->angle) * cube->player->speed;
	if (!is_wall(cube, (int)(new_x / TILE_SIZE), (int)(new_y/ TILE_SIZE)))
	{	
		cube->player->pos.x = new_x;
		cube->player->pos.y = new_y;
	}
}

void	m_right(t_cube *cube)
{
	double	new_x;
	double	new_y;

	new_x = cube->player->pos.x + sin(cube->player->angle) * cube->player->speed; 
	new_y = cube->player->pos.y + cos(cube->player->angle) * cube->player->speed;
	if (!is_wall(cube, (int)(new_x / TILE_SIZE), (int)(new_y/ TILE_SIZE)))
	{	
		cube->player->pos.x = new_x;
		cube->player->pos.y = new_y;
	}
}

void	m_left(t_cube *cube)
{
	double	new_x;
	double	new_y;

	new_x = cube->player->pos.x - sin(cube->player->angle) * cube->player->speed; 
	new_y = cube->player->pos.y - cos(cube->player->angle) * cube->player->speed;
	if (!is_wall(cube, (int)(new_x / TILE_SIZE), (int)(new_y/ TILE_SIZE)))
	{	
		cube->player->pos.x = new_x;
		cube->player->pos.y = new_y;
	}
}
