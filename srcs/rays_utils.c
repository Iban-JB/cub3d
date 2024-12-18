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

void	find_wall_hit(t_cube *cube, t_ray2 *ray, t_Vector2D *prev)
{
	t_bool	hit;

	hit = false;
	while (!hit && ray->step > 0.000001)
	{
		prev->x = ray->pos.x;
		prev->y = ray->pos.y;
		ray->pos.x += ray->dir.x * ray->step;
		ray->pos.y += ray->dir.y * ray->step;
		if (cube->mi->map[(int)(ray->pos.y / TILE_SIZE)][(int) \
		(ray->pos.x / TILE_SIZE)] == '1')
		{
			ray->step /= 10;
			ray->pos.x = prev->x;
			ray->pos.y = prev->y;
			hit = true;
			find_wall_hit(cube, ray, prev);
		}
	}
}
