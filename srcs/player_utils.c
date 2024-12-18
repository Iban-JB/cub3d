/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:21:54 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/12/16 17:58:27 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_bool	in_charset(char *charset, char c)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (true);
	return (false);
}

void	set_spawn_player(t_cube *cube, int i, int j)
{
	char	spawn_dir;

	spawn_dir = cube->mi->map[i][j];
	if (spawn_dir == 'N')
		cube->player->angle = RNORTH;
	else if (spawn_dir == 'S')
		cube->player->angle = RSOUTH;
	else if (spawn_dir == 'E')
		cube->player->angle = 0;
	else if (spawn_dir == 'W')
		cube->player->angle = RWEST;
	cube->player->pos.y = (i * TILE_SIZE) + TILE_SIZE / 2;
	cube->player->pos.x = (j * TILE_SIZE) + TILE_SIZE / 2;
}

void	find_spawn_player(t_cube *cube)
{
	int		i;
	int		j;
	char	*charset;

	charset = "NSEW";
	i = 0;
	while (cube->mi->map && cube->mi->map[i])
	{
		j = 0;
		while (cube->mi->map && cube->mi->map[i][j])
		{
			if (cube->mi->map && in_charset(charset, cube->mi->map[i][j]))
			{
				set_spawn_player(cube, i, j);
				cube->mi->map[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
}
