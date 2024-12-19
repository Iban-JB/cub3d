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

void	loop_read_file(t_cube *cube, t_read_file *file_data)
{
	while (file_data->tp)
	{
		if (!file_data->in_map && (cmp_n_char_after_spaces(file_data->tp, \
		"1", 1) || cmp_n_char_after_spaces(file_data->tp, "0", 1)))
			file_data->in_map = true;
		if (!is_empty_line(file_data->tp) || file_data->in_map)
		{
			file_data->temp_file = \
			tab_join(file_data->final_file, file_data->tp);
			free(file_data->tp);
			ft_free_tab(file_data->final_file);
			if (!file_data->temp_file && close(file_data->fd))
				free_exit(cube);
			file_data->final_file = tab_dup(file_data->temp_file);
			ft_free_tab(file_data->temp_file);
			if (!file_data->final_file && close(file_data->fd))
				free_exit(cube);
		}
		else
			free(file_data->tp);
		file_data->tp = get_next_line(file_data->fd);
	}
}

void	read_stock_file(char *path, t_cube *cube)
{
	t_read_file	file_datas;

	file_datas.in_map = false;
	file_datas.final_file = NULL;
	file_datas.temp_file = NULL;
	file_datas.fd = open(path, O_RDONLY);
	if (file_datas.fd == -1)
		free_exit(cube);
	file_datas.tp = get_next_line(file_datas.fd);
	if (!file_datas.tp)
		free_exit(cube);
	loop_read_file(cube, &file_datas);
	close(file_datas.fd);
	cube->mi->file = tab_dup(file_datas.final_file);
	ft_free_tab(file_datas.final_file);
	if (!cube->mi->file)
		free_exit(cube);
}
