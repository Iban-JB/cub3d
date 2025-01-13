/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:37:50 by ibjean-b          #+#    #+#             */
/*   Updated: 2025/01/06 17:07:29 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_bool	look_up(double angle)
{
	if (angle > 0 && angle < M_PI)
		return (true);
	return (false);
}

double	get_horz_inter(t_cube *cube, t_ray *ray)
{
	printf("player x = %f | y = %f\n ", cube->player->pos.x, cube->player->pos.y);
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(ray->angle);
	printf("step x = %f | y = %f\n", x_step, y_step);
	y_inter = floor(cube->player->pos.y / TILE_SIZE) * TILE_SIZE;
	x_inter = cube->player->pos.x + (y_inter - cube->player->pos.y) / tan(ray->angle);
	if (!look_up(ray->angle))
		y_step *= -1;
	printf("inter x = %f | y = %f\n\n", x_inter, y_inter);
	return (10);
}

double	find_small_inter(t_cube *cube, t_ray *ray)
{
	double	h_inter;
	// double	v_inter;

	h_inter = get_horz_inter(cube, ray);
	// v_inter = get_vert_inter(cube, ray);
	return (h_inter);
}

t_bool	is_minimap(t_cube *cube, int x, int y)
{
	int	mini_x;
	int	mini_y;

	mini_x = TILE_SIZE * cube->mi->len_line;
	mini_y = TILE_SIZE * cube->mi->nb_line;
	if (x <= mini_x && y <= mini_y)
		return (true);
	return (false);
}

void	wall_face_color(t_ray *ray)
{
	if (ray->face == 'N')
		ray->color = RED;
	else if (ray->face == 'S')
		ray->color = GREEN;
	else if (ray->face == 'E')
		ray->color = BLUE;
	else if (ray->face == 'W')
		ray->color = PINK;
}

void	draw_wall(t_cube *cube, t_ray *ray, double wall_dist, int nb_ray)
{
	int	height;
	int	p_top;
	int	p_bot;
	int	pix;

	height = HEIGHT / (wall_dist / TILE_SIZE);
	p_top = (HEIGHT / 2) - (height / 2);
	if (p_top < 0)
		p_top = 0;
	p_bot = (HEIGHT / 2) + (height / 2);
	if (p_bot > HEIGHT)
		p_bot = HEIGHT - 1;
	pix = -1;
	while (++pix < HEIGHT)
	{
		if (!is_minimap(cube, nb_ray, pix) && pix < p_top)
			put_pixel(cube, cube->mi->c->hex, nb_ray, pix);
		else if (!is_minimap(cube, nb_ray, pix) && pix < p_bot)
			put_pixel(cube, ray->color, nb_ray, pix);
		else if (!is_minimap(cube, nb_ray, pix))
			put_pixel(cube, cube->mi->f->hex, nb_ray, pix);
	}
}

void	cast_rays(t_cube *cube)
{
	int		nb_ray;
	t_ray	ray;
	double	wall_dist;

	nb_ray = WIDTH;
	ray.angle = (cube->player->angle - cube->player->fov / 2 * RADIAN);
	while (nb_ray-- > WIDTH - 2)
	{
		wall_dist = find_small_inter(cube, &ray);
		// wall_face_color(&ray);
		// draw_wall(cube, &ray, wall_dist * cos(ray.angle - cube->player->angle),
		// 	nb_ray);
		ray.angle += RADIAN * cube->player->fov / WIDTH;
		draw_ray_minimap(cube, ray.angle, 100);
	}
}
