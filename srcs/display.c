/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:59:52 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/11/20 15:38:35 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    draw_rectangle(t_cube *cube, int x, int y, int color)
{
	int			i;
	int			j;
	t_Vector2D	limit;

	limit.x = (WIDTH - (WIDTH - TILE_SIZE * cube->mi->nb_line));
	limit.y = (WIDTH - (WIDTH - TILE_SIZE * cube->mi->len_line));
	if (!cube->data->img || !cube->data->addr)
		return;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if ((j == 0 || j == TILE_SIZE || i == 0 || i == TILE_SIZE) \
			&& (i + x > 0 && i + x < limit.x && y + j > 0 && y + j < limit.x))
				put_pixel(cube, BLACK, x + i, y + j);
			else if (i + x > 0 && i + x < limit.x && y + j > 0 && y + j < limit.x)
				put_pixel(cube, color, x + i, y + j);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cube *cube)
{
	int	x;
	int	y;

	x = 0;
	while (cube->mi->map[x])
	{
		y = 0;
		while (cube->mi->map[x][y])
		{
			if (cube->mi->map[x][y] == '1')
				draw_rectangle(cube, y * TILE_SIZE, x * TILE_SIZE, WHITE); 
			else if (cube->mi->map[x][y] == '0')
				draw_rectangle(cube, y * TILE_SIZE, x * TILE_SIZE, GRAY);
			y++;
		}
		x++;
	}
	draw_rectangle(cube, cube->player->pos.x - TILE_SIZE / 2, cube->player->pos.y - TILE_SIZE / 2, PINK);
}

// void	draw_ray_minimap(t_cube * cube, double angle, double len)
// {
// 	int			i;
// 	t_Vector2D	dir;
// 	t_Vector2D	ray;
// 	t_Vector2D	limit;

// 	i = -1;
// 	dir.x = cos(angle);
// 	dir.y = -sin(angle);
// 	limit.x = (WIDTH - (WIDTH - TILE_SIZE * cube->mi->nb_line));
// 	limit.y = (WIDTH - (WIDTH - TILE_SIZE * cube->mi->len_line));
// 	while (++i < len) //ajouter la dist de (colision / TILE_SIZE) pour arreter de rayon au bon endroit || param len pour la taille du rayon
// 	{
// 		ray.x = cube->player->pos.x + dir.x * i;
// 		ray.y = cube->player->pos.y + dir.y * i;
// 		if (ray.x > 0 && ray.x < limit.x && ray.y > 0 && ray.y < limit.y)
// 			put_pixel(cube, RED, ray.x, ray.y);
// 		else
// 			break;
// 	}
// }

int	display_cube(t_cube *cube)
{
	handle_moves(cube);
	draw_minimap(cube);
	cast_rays(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->data->img, 0, 0);
	return (1);
}