/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utlis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 17:01:33 by ibjean-b          #+#    #+#             */
/*   Updated: 2024-12-18 17:01:33 by ibjean-b         ###   ########.fr       */
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
		if (j > len_max)
			len_max = j;
		i++;
	}
	return (len_max);
}

void	count_len_and_line(char **map, int *len, int *lines)
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

int	skip_spaces(char *str, size_t i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}
