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
	return (sqrt(pow(ray->x - cube->player->pos.x, 2) + pow(ray->y - cube->player->pos.y, 2)));
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

void	draw_wall(t_cube *cube, double wall_dist, int nb_ray)
{
	int	height;
	int	p_top;
	int	p_bot;
	int	pix;

	height =  HEIGHT / (wall_dist / TILE_SIZE);
	p_top = (HEIGHT / 2) - (height / 2);
	if (p_top < 0)
		p_top = 0;
	p_bot = (HEIGHT / 2) + (height / 2);
	if (p_bot > HEIGHT)
		p_bot = HEIGHT -1;
	pix = -1;
	while (++pix < HEIGHT)
	{
			if (!is_minimap(cube, nb_ray, pix) && pix < p_top)
				put_pixel(cube, cube->mi->c->complete_color, nb_ray, pix);
			else if (!is_minimap(cube, nb_ray, pix) && pix < p_bot)
				put_pixel(cube, GREEN, nb_ray, pix);
			else if (!is_minimap(cube, nb_ray, pix))
				put_pixel(cube, cube->mi->f->complete_color, nb_ray, pix);
	}
}

void	cast_rays(t_cube *cube)
{
	float		nb_ray;
	double		angle;
	double		wall_dist;
	t_Vector2D	ray;

	nb_ray = WIDTH;
	angle = (cube->player->angle - cube->player->fov / 2 * RADIAN);
	while (nb_ray > 0)
	{
		wall_dist = find_small_inter(cube, angle, &ray) * (cos(angle - cube->player->angle));
		draw_wall(cube, wall_dist, nb_ray);
		draw_ray_minimap(cube, angle, wall_dist);
		angle += (RADIAN * cube->player->fov / WIDTH) * 0.25;
		nb_ray -= 0.25;
	}	
}
