/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:49:55 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/12/16 16:09:59 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_color(t_color *color)
{
	if (color)
	{
		ft_free_tab(color->rgb);
		free(color);
	}
}

void	free_mlx(t_cube *cube)
{
	if (cube)
	{
		if (cube->data)
		{
			if (cube->data->img)
				mlx_destroy_image(cube->mlx, cube->data->img);
			free(cube->data);
		}
		if (cube->win)
			mlx_destroy_window(cube->mlx, cube->win);
		if (cube->mlx)
		{
			mlx_destroy_display(cube->mlx);
			free(cube->mlx);
		}
	}
}

void	free_map_info(t_cube *cube)
{
	if (cube && cube->mi)
	{
		if (cube->mi->file)
			ft_free_tab(cube->mi->file);
		if (cube->mi->map)
			ft_free_tab(cube->mi->map);
		if (cube->mi->n)
			free(cube->mi->n);
		if (cube->mi->s)
			free(cube->mi->s);
		if (cube->mi->e)
			free(cube->mi->e);
		if (cube->mi->w)
			free(cube->mi->w);
		if (cube->mi->c)
			free_color(cube->mi->c);
		if (cube->mi->f)
			free_color(cube->mi->f);
		free(cube->mi);
	}
}

void	free_exit(t_cube *cube)
{
	if (cube)
	{
		if (cube->player)
			free(cube->player);
		if (cube->mi)
			free_map_info(cube);
		free_mlx(cube);
		free(cube);
	}
	exit(1);
}
