/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 16:29:39 by ibjean-b          #+#    #+#             */
/*   Updated: 2024-12-18 16:29:39 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "msg.h"

t_bool	check_extension(char *path, char *extension)
{
	if (ft_strncmp(path + (ft_strlen(path) - 4), extension, 5))
		return (false);
	return (true);
}

t_bool	check_dir(char *path)
{
	if (open(path, __O_DIRECTORY) == -1)
		return (true);
	return (false);
}

t_bool	validate_file(char *path, char *extension)
{
	if (!check_extension(path, extension))
	{
		ft_printf(INV_EXTENSION);
		return (false);
	}
	if (!check_dir(path))
	{
		ft_printf(INV_DIR);
		return (false);
	}
	return (true);
}

void	check_file(t_cube *cube)
{
	size_t	i;

	i = -1;
	while (cube->mi->file[++i])
	{
		if (cmp_n_char_after_spaces(cube->mi->file[i], "NO ", 3) && !cube->mi->check.n)
			cube->mi->check.n = true;
		else if (cmp_n_char_after_spaces(cube->mi->file[i], "SO ", 3) && !cube->mi->check.s)
			cube->mi->check.s = true;
		else if (cmp_n_char_after_spaces(cube->mi->file[i], "WE ", 3) && !cube->mi->check.w)
			cube->mi->check.w = true;
		else if (cmp_n_char_after_spaces(cube->mi->file[i], "EA ", 3) && !cube->mi->check.e)
			cube->mi->check.e = true;
		else if (cmp_n_char_after_spaces(cube->mi->file[i], "F ", 2) && !cube->mi->check.f)
			cube->mi->check.f = true;
		else if (cmp_n_char_after_spaces(cube->mi->file[i], "C ", 2) && !cube->mi->check.c)
			cube->mi->check.c = true;
		else if (cmp_n_char_after_spaces(cube->mi->file[i], "1", 1) || cmp_n_char_after_spaces(cube->mi->file[i], "0", 1))
		{
			if (!cube->mi->check.m)
				cube->mi->check.m = true;
			continue ;
		}
		else
		{
			ft_printf("%s%s\n", INV_LINE, cube->mi->file[i]);
			free_exit(cube);
		}
	}
}
