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

double	get_ray_angle(t_cube *cube, int nb_ray)
{
	double	ray_angle;

	(void)nb_ray;
	// printf("player ray angle = %f\n", sin(cube->player->angle));
	ray_angle = (cube->player->angle - cube->player->fov / 2);
	// printf("first ray angle = %f\n\n", ray_angle);
	return (ray_angle);
}

double	get_horz_inter(t_cube *cube, double ray_angle)
{
	t_Vector2D	dir;
	t_Vector2D	ray;

	dir.x = cos(ray_angle);
	dir.y = -sin(ray_angle);
	return (0);
}

double	get_vert_inter(t_cube *cube, double angle)
{
	(void)cube;
	(void)angle;
	return (0);
}

double	find_small_inter(t_cube *cube, double angle)
{
	double	vert_inter;
	double	horz_inter;

	horz_inter = get_horz_inter(cube, angle);
	vert_inter = get_vert_inter(cube, angle);
	if (horz_inter < vert_inter)
		return (horz_inter);
	return (vert_inter);
}

void	cast_rays(t_cube *cube)
{
	int		nb_ray;
	double	angle;
	double	wall_dist;

	nb_ray = -1;
	angle = (cube->player->angle - cube->player->fov / 2 * RADIAN);
	while (++nb_ray < 1)
	{
		wall_dist = find_small_inter(cube, angle);
		draw_ray_minimap(cube, angle, 1000);
		angle += RADIAN * cube->player->fov / WIDTH;
	}	
}
