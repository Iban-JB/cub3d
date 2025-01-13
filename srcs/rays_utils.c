/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 17:20:08 by ibjean-b          #+#    #+#             */
/*   Updated: 2025/01/06 17:08:27 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	get_face(t_Vector2D hit, int x, int y)
{
	t_Vector2D	center;
	double		angle;

	center.x = x * TILE_SIZE + TILE_SIZE / 2;
	center.y = y * TILE_SIZE + TILE_SIZE / 2;
	angle = atan2(hit.y - center.y, hit.x - center.x);
	if (angle >= -M_PI / 4 && angle < M_PI / 4)
		return ('E');
	if (angle >= M_PI / 4 && angle < 3 * M_PI / 4)
		return ('S');
	if (angle >= 3 * M_PI / 4 || angle < -3 * M_PI / 4)
		return ('W');
	else
		return ('N');
}
