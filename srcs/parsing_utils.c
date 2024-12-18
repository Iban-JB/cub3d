/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 17:13:49 by ibjean-b          #+#    #+#             */
/*   Updated: 2024-12-18 17:13:49 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "msg.h"

t_bool	cmp_n_char_after_spaces(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	i = skip_spaces(s1, i);
	while (i < n)
	{
		if (s1[i] != s2[j])
			return (false);
		i++;
		j++;
	}
	return (true);
}

static t_bool	check_first_and_last_line(char *line)
{
	size_t	i;

	i = -1;
	if (!line || !ft_strncmp(line, "", 1))
		return (false);
	while (line[++i])
		if (line[i] != 'X' && line[i] != '1')
			return (false);
	return (true);
}

static t_bool	check_segment(char **map, size_t j, size_t *player, size_t *i)
{
	if (map[j][*i] != '1')
		return (false);
	while (map[j][*i] && map[j][*i] != 'X')
	{
		if (map[j][*i] == 'N' || map[j][*i] == 'S' || map[j][*i] == 'E'
			|| map[j][*i] == 'W')
		{
			(*player)++;
			(*i)++;
			continue ;
		}
		if (map[j][*i] != '1' && map[j][*i] != '0')
			return (false);
		if (map[j][*i] == '0' && (map[j - 1][*i] == 'X' || map[j
				+ 1][*i] == 'X'))
			return (false);
		(*i)++;
	}
	if (map[j][*i - 1] != '1')
		return (false);
	return (true);
}

static t_bool	check_line(char **map, size_t j, size_t *player)
{
	size_t	i;

	i = 0;
	if (!map[j] || !ft_strncmp(map[j], "", 1))
		return (false);
	while (map[j][i])
	{
		while (map[j][i] == 'X')
			i++;
		if (map[j][i])
			if (!check_segment(map, j, player, &i))
				return (false);
	}
	return (true);
}

t_bool	is_map_valid(char **map)
{
	size_t	i;
	size_t	player;

	i = 0;
	player = 0;
	if (!check_first_and_last_line(map[i]))
		return (false);
	while (map[++i])
	{
		if (!map[i + 1])
		{
			if (!check_first_and_last_line(map[i]))
				return (false);
		}
		else
		{
			if (!check_line(map, i, &player))
				return (false);
		}
	}
	if (player != 1)
		return (false);
	return (true);
}
