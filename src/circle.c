/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:29:17 by ademurge          #+#    #+#             */
/*   Updated: 2023/02/27 11:46:25 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	circle(t_cub *cub, int r, int color)
{
	float		rad;
	int			x;
	int			y;
	float		angle;

	(void)color;
	angle = 0;
	while (angle <= 360)
	{
		rad = angle * (M_PI / 180);
		x = (cub->plr.real_x / MAP_DIV) + r * cos(rad);
		y = (cub->plr.real_y / MAP_DIV) + r * sin(rad);
		angle += 0.1;
	}
}

void	init_ray(t_ray *ray)
{
	ray->angle = 0;
	ray->dir = 0;
	ray->side = 0;
	ray->l = 0;
	ray->real_x = 0;
	ray->real_y = 0;
}

t_ray	intersection(int cx, int cy, float r, float angle)
{
	t_ray		dir;
	float		rad;

	init_ray(&dir);
	rad = angle * (M_PI / 180);
	dir.real_x = cx + (r * cos(rad));
	dir.real_y = cy + (r * sin(rad));
	return (dir);
}
