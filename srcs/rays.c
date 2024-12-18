/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:37:50 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/12/17 14:14:22 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char get_face(t_Vector2D hit, int x, int y)
{
	t_Vector2D center;
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
	while (!hit)
	{
		prev->x = ray->pos.x;
		prev->y = ray->pos.y;
		ray->pos.x += ray->dir.x * ray->step;
		ray->pos.y += ray->dir.y * ray->step;
		if (cube->mi->map[(int)(ray->pos.y / TILE_SIZE)][(int)(ray->pos.x / TILE_SIZE)] == '1')
			hit = true;
	}
	hit = false;
	ray->step = 0.00001;
	ray->pos.x = prev->x;
	ray->pos.y = prev->y;
	while (!hit)
	{
		prev->x = ray->pos.x;
		prev->y = ray->pos.y;
		ray->pos.x += ray->dir.x * ray->step;
		ray->pos.y += ray->dir.y * ray->step;
		if (cube->mi->map[(int)(ray->pos.y / TILE_SIZE)][(int)(ray->pos.x / TILE_SIZE)] == '1')
			hit = true;
	}
}

double	get_wall_dist(t_cube *cube, t_ray2 *ray)
{
	t_Vector2D	prev;
	
	ray->step = 0.1;
	ray->pos.y = (cube->player->pos.y);
	ray->pos.x = (cube->player->pos.x);
	ray->dir.x = cos(ray->angle);
	ray->dir.y = -sin(ray->angle);
	find_wall_hit(cube, ray, &prev);
	ray->face = get_face(ray->pos, (int)ray->pos.x / TILE_SIZE, (int)ray->pos.y / TILE_SIZE);
	return (sqrt(pow(prev.x - cube->player->pos.x, 2) + pow(prev.y - cube->player->pos.y, 2)));
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

void	wall_face_color(t_ray2 *ray)
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

void	draw_wall(t_cube *cube, t_ray2 *ray, double wall_dist, int nb_ray)
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
	t_ray2	ray;
	double	wall_dist;

	nb_ray = WIDTH;
	ray.angle = (cube->player->angle- cube->player->fov / 2 * RADIAN);
	while (nb_ray-- > 0)
	{
		wall_dist = get_wall_dist(cube, &ray);
		wall_face_color(&ray);
		draw_wall(cube, &ray, wall_dist * cos(ray.angle - cube->player->angle), nb_ray);
		draw_ray_minimap(cube, ray.angle, wall_dist);
		ray.angle += RADIAN * cube->player->fov / WIDTH;
	}	
}
