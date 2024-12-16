/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:29:31 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/10/23 17:56:37 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_width_max(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		i++;
	}
	return (i);
}

int	get_len_max(char **map)
{
	int	i;
	int	j;
	int	len_max;

	i = 0;
	len_max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j < len_max)
			len_max = j;
		i++;
	}
	return (len_max);
}

void	count_len_and_line(char	**map, int *len, int *lines)
{
	int	i;
	int	j;
	int	len_max;
	
	len_max = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > len_max)
			len_max = j;
		i++;
	}
	*len = len_max;
	*lines = i;
}

void	fill_new_map(t_cube *cube, char **new_map, int len_max)
{
	int		i;
	int		len_cpy;
	char	*line;

	i = 0;
	line = cube->mi->map[i];
	while (line)
	{
		new_map[i] = ft_calloc(1, len_max + 1);
		len_cpy = ft_strlen(line);
		ft_memcpy(new_map[i], line, len_cpy);
		while (len_cpy < len_max)
			new_map[i][len_cpy++] = ' ';
		new_map[i][len_cpy] = '\0';
		line = cube->mi->map[++i];
	}
}

void	find_and_repalce(char **new_map, char c, char new_c)
{
	int	i;
	int	j;
	
	i = 0;
	while (new_map[i])
	{
		j = 0;
		while (new_map[i][j])
		{
			if (new_map[i][j] == c)
				new_map[i][j] = new_c;
			j++;
		}
		i++;
	}
}

void	modify_char_in_map(t_cube *cube, char c, char new_c)
{
	int		len;
	int		nb_line;
	char	**new_map;
	
	len = 0;
	nb_line = 0;
	count_len_and_line(cube->mi->map, &len, &nb_line);
	new_map = ft_calloc(nb_line + 1, sizeof(char *));
	if (!new_map)
		free_exit(cube);
	fill_new_map(cube, new_map, len);
	find_and_repalce(new_map, c, new_c);
	ft_free_tab(cube->mi->map);
	cube->mi->map = tab_dup(new_map);
	ft_free_tab(new_map);
}
