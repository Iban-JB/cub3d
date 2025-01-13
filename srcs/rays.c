/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:37:50 by ibjean-b          #+#    #+#             */
/*   Updated: 2025/01/13 18:40:53 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_bool	unit_cirle(double angle, char axis)
{
	if (axis == 'x')
	{
		if (angle > 0 && angle < M_PI / 2)
			return (true);
	}
	else if (axis == 'y')
	{
		if (angle > 3 * M_PI / 2 && angle < M_PI / 2)
			return (true);
	}
	return (false);
}

double	get_horz_inter(t_cube *cube, t_ray *ray)
{
	// printf("player x = %f | y = %f\n ", cube->player->pos.x, cube->player->pos.y);
	int		hit;
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;

	hit = 0;
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(ray->angle);
	// printf("step x = %f | y = %f\n", x_step, y_step);
	if (ray->angle < M_PI)
	{
		y_inter = floor(cube->player->pos.y / TILE_SIZE) * TILE_SIZE - 1;
	}
	else 
	{
		y_inter = floor(cube->player->pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		x_step *= -1;
		y_step *= -1;
	}
	if (ray->angle == 0 || ray->angle == M_PI)
		return (-1);
	x_inter = cube->player->pos.x - (y_inter - cube->player->pos.y) / tan(ray->angle);
	while (!hit)
	{
		//draw_rectangle(cube, x_inter, y_inter, GREEN, 10);
		if (y_inter < 0 || x_inter < 0 || y_inter > TILE_SIZE * cube->mi->nb_line || x_inter > TILE_SIZE * cube->mi->len_line)
			break ;
		if (cube->mi->map[(int)(y_inter / TILE_SIZE)][(int)(x_inter / TILE_SIZE)] == '1')
			hit = 1;
		x_inter += x_step;
		y_inter -= y_step;
	}
	// if (!look_up(ray->angle))
	// 	y_step *= -1;
	
	printf("inter x = %f | y = %f\n\n", x_inter, y_inter);
	return (sqrt(pow(x_inter - cube->player->pos.x, 2) + pow(y_inter - cube->player->pos.y, 2)));
}

double	get_vert_inter(t_cube *cube, t_ray *ray)
{
	// printf("player x = %f | y = %f\n ", cube->player->pos.x, cube->player->pos.y);
	int		hit;
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;

	hit = 0;
	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(ray->angle);
	if (ray->angle == RNORTH || ray->angle == RSOUTH)
		return (-1);
	// printf("step x = %f | y = %f\n", x_step, y_step);
	if (ray->angle < RNORTH || ray->angle > RSOUTH)
	{
		x_inter = floor(cube->player->pos.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		x_step *= -1;
		y_step *= -1;
	}
	else 
		x_inter = floor(cube->player->pos.x / TILE_SIZE) * TILE_SIZE - 1;
	y_inter = cube->player->pos.y - (x_inter - cube->player->pos.x) * tan(ray->angle);
	while (!hit)
	{
		// draw_rectangle(cube, x_inter, y_inter, RED, 10);
		if (y_inter < 1 || x_inter < 1 || y_inter > TILE_SIZE * cube->mi->nb_line - 1 || x_inter > TILE_SIZE * cube->mi->len_line - 1)
			break ;
		if (cube->mi->map[(int)(y_inter / TILE_SIZE)][(int)(x_inter / TILE_SIZE)] == '1')
			hit = 1;
		x_inter -= x_step;
		y_inter += y_step;
	}
	return (sqrt(pow(x_inter - cube->player->pos.x, 2) + pow(y_inter - cube->player->pos.y, 2)));
}

double	find_small_inter(t_cube *cube, t_ray *ray)
{
	double	h_inter;
	double	v_inter;

	h_inter = get_horz_inter(cube, ray);
	v_inter = get_vert_inter(cube, ray);
	if (h_inter < v_inter || v_inter == -1)
	{
		printf("h_inter = %f\n", h_inter);
		return (h_inter);
	}
	else if (v_inter < h_inter || h_inter == -1)
	{
		printf("v_inter = %f\n", v_inter);
		return (v_inter);
	}
	else
		return (-1);
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
	if (ray.angle < 0)
		ray.angle += 2 * M_PI;
	while (nb_ray-- > 0)
	{
		wall_dist = find_small_inter(cube, &ray);
		printf("angle = %f\n", ray.angle);
		wall_face_color(&ray);
		draw_wall(cube, &ray, wall_dist * cos(ray.angle - cube->player->angle),
			nb_ray);
		ray.angle += RADIAN * cube->player->fov / WIDTH;
		draw_ray_minimap(cube, ray.angle, wall_dist);
	}
}
