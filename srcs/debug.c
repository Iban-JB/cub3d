#include "cub3D.h"

void    print_map_info(t_cube *cube)
{
    int i;

    i = -1;
	// while (cube->mi->file[++i])
	// 	ft_printf("ligne %i (len = %d) : %s\n", i, (int)ft_strlen(cube->mi->file[i]), cube->mi->file[i]);
    i = -1;
    ft_printf("\n\n\n\n\n\n");
    ft_printf("%s\n", cube->mi->n);
    ft_printf("%s\n", cube->mi->s);
    ft_printf("%s\n", cube->mi->e);
    ft_printf("%s\n", cube->mi->w);
    printf("%ld\n", cube->mi->c->hex);
    while (cube->mi->map[++i])
        ft_printf("%s\n", cube->mi->map[i]);
}