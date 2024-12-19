/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 17:20:08 by ibjean-b          #+#    #+#             */
/*   Updated: 2024-12-18 17:20:08 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	get_face(t_Vector2D hit, int x, int y)
{
	t_Vector2D	center;
	double		angle;

	center.x = x * TILE_SIZE + TILE_SIZE / 2;
	center.y = y * TILE_SIZE + TILE_SIZE / 2;
	angle = atan2(hit.y - center.y, hit.x - center.x);
	if (angle >= -M_PI / 4 && angle < M_PI / 4)
		return ('E');
	if (angle >= M_PI / 4 && angle < 3 * M_PI / 4)
		return ('S');
	if (angle >= 3 * M_PI / 4 || angle < -3 * M_PI / 4)
		return ('W');
	else
		return ('N');
}

void	find_wall_hit(t_cube *cube, t_ray *ray, t_Vector2D *prev)
{
	t_bool	hit;
	int		map_x;
	int		map_y;

	hit = false;
	while (!hit && ray->step > 0.000001)
	{
		prev->x = ray->pos.x;
		prev->y = ray->pos.y;
		ray->pos.x += ray->dir.x * ray->step;
		ray->pos.y += ray->dir.y * ray->step;
		map_x = (int)(ray->pos.x / TILE_SIZE);
		map_y = (int)(ray->pos.y / TILE_SIZE);
		if (cube->mi->map[map_y][map_x] == '1')
		{
			ray->step /= 10;
			ray->pos.x = prev->x;
			ray->pos.y = prev->y;
			hit = true;
			find_wall_hit(cube, ray, prev);
		}
	}
}
