/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:59:52 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/12/16 17:48:44 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rectangle(t_cube *cube, int x, int y, int color, int size)
{
	int	i;
	int	j;

	if (!cube->data->img || !cube->data->addr)
		return ;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j == 0 || j == size || i == 0 || i == size)
				put_pixel(cube, BLACK, x + i, y + j);
			else
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
				draw_rectangle(cube, y * TILE_SIZE, x * TILE_SIZE, WHITE, TILE_SIZE);
			else if (cube->mi->map[x][y] == '0')
				draw_rectangle(cube, y * TILE_SIZE, x * TILE_SIZE, GRAY, TILE_SIZE);
			y++;
		}
		x++;
	}
	draw_rectangle(cube, cube->player->pos.x - TILE_SIZE / 2, cube->player->pos.y - TILE_SIZE / 2, PINK, TILE_SIZE);
}

void	draw_ray_minimap(t_cube *cube, double angle, double wall_dst)
{
	int		i;
	t_ray2	ray;

	i = -1;
	ray.dir.x = cos(angle);
	ray.dir.y = -sin(angle);
	ray.pos.x = cube->player->pos.x / TILE_SIZE;
	ray.pos.y = cube->player->pos.y / TILE_SIZE;
	while (++i < wall_dst)
	{
		ray.pos.x = cube->player->pos.x + ray.dir.x * i;
		ray.pos.y = cube->player->pos.y + ray.dir.y * i;
		put_pixel(cube, RED, ray.pos.x, ray.pos.y);
	}
}

int	display_cube(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= WIDTH && j <= HEIGHT)
	{
		put_pixel(cube, BLACK, i, j);
		if (i == WIDTH)
		{
			i = 0;
			j++;
		}
		i++;
	}
	handle_moves(cube);
	draw_minimap(cube);
	cast_rays(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->data->img, 0, 0);
	return (1);
}
