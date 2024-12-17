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
	// update_pos_player(cube, old_posx, old_posy);
	
}

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
	// printf("x = %d, y = %d, c = %c\n", x, y, cube->mi->map[x][y]);
	if (cube->mi->map[(int)(x + margin.x) / TILE_SIZE][(int)(y + margin.y) / TILE_SIZE] && cube->mi->map[(int)(x + margin.x) / TILE_SIZE][(int)(y + margin.y) / TILE_SIZE] && x >= 0 && y >= 0 && cube->mi->map[(int)(x + margin.x) / TILE_SIZE][(int)(y + margin.y) / TILE_SIZE] == '1')
		return (true);
	return (false);
}


//AJOUTER LES COLISIONS ICI ->

// void	update_pos_player(t_cube *cube, double x, double y)
// {
// 	int	new_x;
// 	int	new_y;

// 	new_x = (x + MARGIN) / TILE_SIZE;
// 	new_y = (y + MARGIN) / TILE_SIZE;
// 	printf("new : x = %d && y = %d\n", new_x, new_y));
// 	printf("map : %c\n", cube->mi->map[new_x][new_y]);
// 	if (is_wall(cube, (int)((x + MARGIN) / TILE_SIZE), (int)((y + MARGIN)/ TILE_SIZE)))
// 	{
// 		cube->player->pos.x = x;
// 		cube->player->pos.y = y;
// 	}
// 	else
// 		printf("you're not a ghost\n");
// }

void	m_forward(t_cube *cube)
{
	double	new_y;
	double	new_x;

	new_x = cube->player->pos.x + cos(cube->player->angle) * cube->player->speed; 
	new_y = cube->player->pos.y - sin(cube->player->angle) * cube->player->speed;	
//	update_pos_player(cube, new_x, new_y))
	if (!is_wall(cube, new_x, new_y, 0))
	{	
		cube->player->pos.x = new_x; // A enlever quand les colisions sont OK !
		cube->player->pos.y = new_y; // A enlever quand les colisions sont OK 
	}
}

void	m_backward(t_cube *cube)
{
	double	new_y;
	double	new_x;

	new_x = cube->player->pos.x - cos(cube->player->angle) * cube->player->speed; 
	new_y = cube->player->pos.y + sin(cube->player->angle) * cube->player->speed;
	if (!is_wall(cube, new_x, new_y, 1))
	{	
		cube->player->pos.x = new_x; // A enlever quand les colisions sont OK !
		cube->player->pos.y = new_y; // A enlever quand les colisions sont OK !
	}
	// update_pos_player(cube, new_x, new_y));
}

void	m_right(t_cube *cube)
{
	double	new_x;
	double	new_y;

	new_x = cube->player->pos.x + sin(cube->player->angle) * cube->player->speed; 
	new_y = cube->player->pos.y + cos(cube->player->angle) * cube->player->speed;
	if (!is_wall(cube, new_x, new_y, 0))
	{	
		cube->player->pos.x = new_x; // A enlever quand les colisions sont OK !
		cube->player->pos.y = new_y; // A enlever quand les colisions sont OK !
	}
	// update_pos_player(cube, new_x, cube->player->pos.y);
}

void	m_left(t_cube *cube)
{
	double	new_x;
	double	new_y;

	new_x = cube->player->pos.x - sin(cube->player->angle) * cube->player->speed; 
	new_y = cube->player->pos.y - cos(cube->player->angle) * cube->player->speed;
	if (!is_wall(cube, new_x, new_y, 2))
	{	
		cube->player->pos.x = new_x; // A enlever quand les colisions sont OK !
		cube->player->pos.y = new_y; // A enlever quand les colisions sont OK !
	}
	// update_pos_player(cube, new_x, cube->player->pos.y);
}
