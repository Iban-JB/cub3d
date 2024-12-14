/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-03 15:37:50 by ibjean-b          #+#    #+#             */
/*   Updated: 2024-12-03 15:37:50 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ray(t_cube *cube, t_Vector2D *ray)
{
	t_Vector2D	limit;

	limit.x = (WIDTH - (WIDTH - TILE_SIZE * cube->mi->nb_line));
	limit.y = (HEIGHT - (HEIGHT - TILE_SIZE * cube->mi->len_line));
	if (ray->x > 0 && ray->x < limit.x && ray->y > 0 && ray->y < limit.y)
			put_pixel(cube, RED, ray->x, ray->y);
}

double	find_small_inter(t_cube *cube, double angle, t_Vector2D *ray)
{
	int			hit;
	int			side;
	double		step;
	t_Vector2D	dir;

	hit = 0;
	side = 0;
	step = 0.5;
	ray->y = cube->player->pos.y;
	ray->x = cube->player->pos.x;
	dir.x = cos(angle);
	dir.y = -sin(angle);
	while (!hit)
	{
		ray->x += dir.x * step;
		ray->y += dir.y * step;
		if (cube->mi->map[(int)(ray->y / TILE_SIZE)][(int)(ray->x / TILE_SIZE)] == '1')
			hit = 1;
		else
			draw_ray(cube, ray);
	}
	ray->x -= dir.x * step;
	ray->y -= dir.y * step;
	return (sqrt(pow(2, fabs(ray->x - cube->player->pos.x)) + pow(2, fabs(ray->y - cube->player->pos.y))));
}

void	cast_rays(t_cube *cube)
{
	int			nb_ray;
	double		angle;
	double		wall_dist;
	t_Vector2D	ray;

	nb_ray = -1;
	angle = (cube->player->angle - cube->player->fov / 2 * RADIAN);
	while (++nb_ray < WIDTH)
	{
		wall_dist = find_small_inter(cube, angle, &ray);
		printf("walldist = %f\n", wall_dist);
		// draw_ray_minimap(cube, angle, wall_dist);
		angle += RADIAN * cube->player->fov / WIDTH;
	}	
}
