#include "cub3D.h"
#include "msg.h"

static t_bool	get_texture(char *line, t_cube *cube, char **texture, char *id)
{
	char	**split;
	int		j;

	j = -1;
	if (!cmp_n_char_after_spaces(line, id, 3))
		return (false);
	split = ft_split(line, ' ');
	if (!split)
		free_exit(cube);
	while (split[++j])
		;
	if (j != 2)
	{
		ft_free_tab(split);
		return (false);
	}
	*texture = ft_strdup(split[1]);
	ft_free_tab(split);
	if (!(*texture))
		free_exit(cube);
	if (!validate_file(*texture, ".xpm"))
		free_exit(cube);
	return (true);
}

static t_bool	is_rgb_format(char **rgb)
{
	int	i;
	int	j;

	i = -1;
	while (rgb[++i])
	{
		j = -1;
		while (rgb[i][++j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (false);
		}
		if (ft_atoi(rgb[i]) > 255)
			return (false);
	}
	if (i != 3)
		return (false);
	return (true);
}

static t_bool	get_color(char *line, t_cube *cube, t_color	**color, char *id)
{
	char	**split;
	int	j;

	j = -1;
	if (!cmp_n_char_after_spaces(line, id, 2))
		return (false);
	split = ft_split(line, ' ');
	if (!split)
		free_exit(cube);
	while (split[++j])
		;
	if (j != 2)
	{
		ft_free_tab(split);
		return (false);
	}
	(*color)->rgb = ft_split(split[1], ',');
	ft_free_tab(split);
	if (!(*color)->rgb)
		free_exit(cube);
	if (!is_rgb_format((*color)->rgb))
		return (false);
	(*color)->hex = ((ft_atoi((*color)->rgb[0]) & 0xff) << 16) + ((ft_atoi((*color)->rgb[1]) & 0xff) << 8) + (ft_atoi((*color)->rgb[2]) & 0xff);
	(*color)->complete_color = true;
	return (true);
}

t_bool	assign_textures(char **file, t_cube *cube)
{
	size_t	i;

	i = 0;
	while (file[i])
	{
		if (get_texture(file[i], cube, &cube->mi->n, "NO "))
			i++;
		else if (get_texture(file[i], cube, &cube->mi->s, "SO "))
			i++;
		else if (get_texture(file[i], cube, &cube->mi->w, "WE "))
			i++;
		else if (get_texture(file[i], cube, &cube->mi->e, "EA "))
			i++;
		else if (get_color(file[i], cube, &cube->mi->c, "C "))
			i++;
		else if (get_color(file[i], cube, &cube->mi->f, "F "))
			i++;
		else
			i++;
		if (cube->mi->n && cube->mi->s && cube->mi->w && cube->mi->e && cube->mi->c->complete_color && cube->mi->f->complete_color)
			return (true);
	}
	return (false);
}

t_bool	is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	if (!ft_strncmp(line, "\n", 1))
		return (true);
	while (line && ft_isspace(line[i]))
		i++;
	if (line[i] == '\n')
		return (true);
	return (false);
}

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

void	find_map(t_cube *cube)
{
	size_t	i;
	size_t	j;
	char	*charset;

	i = 0;
	charset = "NSWEFC";
	while (cube->mi->file[i])
	{
		j = 0;
		while (ft_isspace(cube->mi->file[i][j]))
			j++;
		if (cube->mi->file[i][j] && !ft_strchr(charset, cube->mi->file[i][j]) \
		&& (cube->mi->file[i][j] == '0' || cube->mi->file[i][j] == '1'))
		{
			j = i;
			while (cube->mi->file[j++])
				if (cube->mi->file[j] && ft_strchr(cube->mi->file[j], 'X'))
					free_exit(cube);
			cube->mi->map = tab_dup(cube->mi->file + i);
			break;
		}
		else
			i++;
	}
}


t_bool	parse_map(char *path, t_cube *cube)
{
	read_stock_file(path, cube);
	check_file(cube);
	if (!assign_textures(cube->mi->file, cube))
		free_exit(cube);
	
	find_map(cube);
	modify_char_in_map(cube, ' ', 'X');
	if (!is_map_valid(cube->mi->map))
		free_exit(cube);
	print_map_info(cube);
	modify_char_in_map(cube, 'X', '1');
	return (true);
}
