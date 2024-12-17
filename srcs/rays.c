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

double	get_ray_angle(t_cube *cube, int nb_ray)
{
	double	ray_angle;

	(void)nb_ray;
	ray_angle = (cube->player->angle - cube->player->fov / 2);
	return (ray_angle);
}

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

double	get_inter(t_cube *cube, double ray_angle)
{
	int			hit;
	double		step;

	step = 0.125;
	hit = 0;
	cube->ray->map.y = (cube->player->pos.y); // - (TILE_SIZE / 2);
	cube->ray->map.x = (cube->player->pos.x);	
	cube->ray->dir.x = cos(ray_angle);
	cube->ray->dir.y = sin(-ray_angle);
	while (hit == 0)
	{
		cube->ray->prev.x = cube->ray->map.x;
		cube->ray->prev.y = cube->ray->map.y;
		cube->ray->map.x += cube->ray->dir.x * step;
		cube->ray->map.y += cube->ray->dir.y * step;
		if (cube->mi->map[(int)(cube->ray->map.y / TILE_SIZE)][(int)(cube->ray->map.x / TILE_SIZE)] == '1')
			hit = 1;
	}
	cube->ray->face = get_face(cube->ray->map, (int)cube->ray->map.x / TILE_SIZE, (int)cube->ray->map.y / TILE_SIZE);
	return (sqrt(pow(cube->ray->prev.x - cube->player->pos.x, 2) + pow(cube->ray->prev.y - cube->player->pos.y, 2)));
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

void	wall_face_color(t_cube *cube)
{
	if (cube->ray->face == 'N')
		cube->ray->color = RED;
	else if (cube->ray->face == 'S')
		cube->ray->color = GREEN;
	else if (cube->ray->face == 'E')
		cube->ray->color = BLUE;
	else if (cube->ray->face == 'W')
		cube->ray->color = PINK;
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
				put_pixel(cube, cube->mi->c->hex, nb_ray, pix);
			else if (!is_minimap(cube, nb_ray, pix) && pix < p_bot)
				put_pixel(cube, cube->ray->color, nb_ray, pix);
			else if (!is_minimap(cube, nb_ray, pix))
				put_pixel(cube, cube->mi->f->hex, nb_ray, pix);
	}
}

void	cast_rays(t_cube *cube)
{
	int		nb_ray;
	double	angle;
	double	wall_dist;

	int		i;
	nb_ray = WIDTH;
	angle = (cube->player->angle- cube->player->fov / 2 * RADIAN);
	while (nb_ray-- > 0)
	{
		i = -1;
		wall_dist = get_inter(cube, angle);
		wall_face_color(cube);
		draw_wall(cube, wall_dist, nb_ray);
		draw_ray_minimap(cube, angle, wall_dist);
		angle += RADIAN * cube->player->fov / WIDTH;
	}	
}
