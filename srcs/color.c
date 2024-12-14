/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:39:04 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/10/24 15:51:41 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_cube *cube, unsigned int color, int x, int y)
{
	char	*dst;
	
	if (!cube || !cube->data->addr || x < 0 || y < 0  || x > WIDTH || y > HEIGHT)
		return ;
	dst = cube->data->addr + \
	(y * cube->data->line_length + x * (cube->data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
	