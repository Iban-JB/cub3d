/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 17:32:38 by ibjean-b          #+#    #+#             */
/*   Updated: 2024-12-18 17:32:38 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	read_stock_file(char *path, t_cube *cube)
{
	int		fd;
	char	*tp;
	char	**temp_file;
	char	**final_file;
	t_bool	in_map;

	in_map = false;
	final_file = NULL;
	temp_file = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		free_exit(cube);
	tp = get_next_line(fd);
	if (!tp)
		free_exit(cube);
	while (tp)
	{
		if (!in_map)
			if (cmp_n_char_after_spaces(tp, "1", 1) || cmp_n_char_after_spaces(tp, "0", 1))
				in_map = true;
		if (!is_empty_line(tp) || in_map)
		{
			temp_file = tab_join(final_file, tp);
			free(tp);
			ft_free_tab(final_file);
			if (!temp_file)
			{
				close(fd);
				free_exit(cube);
			}
			final_file = tab_dup(temp_file);
			ft_free_tab(temp_file);
			if (!final_file)
			{
				close(fd);
				free_exit(cube);
			}
		}
		else
			free(tp);
		tp = get_next_line(fd);
	}
	close(fd);
	cube->mi->file = tab_dup(final_file);
	ft_free_tab(final_file);
	if (!cube->mi->file)
		free_exit(cube);
}
