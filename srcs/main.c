#include "cub3D.h"
#include "msg.h"

int	main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc != 2 || !validate_file(argv[1], ".cub"))
		printf(INV_ARGS);
	else
	{
		cube = ft_calloc(1, sizeof(t_cube));
		if (!cube)
			return (1);
		set_cube_null(cube);
		if (parse_map(argv[1], cube) && init_cube(cube))
			mlx_loop(cube->mlx);
		free_exit(cube);
	}
	return (0);
}
