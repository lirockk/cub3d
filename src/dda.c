/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:29:17 by ademurge          #+#    #+#             */
/*   Updated: 2023/01/20 16:55:05 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int	check_walls(int x, int y, t_cub *cub)
{
	if (cub->map.map[y / SIZE][x / SIZE] == '1')
		return (1);
	// if ((cub->map.map[y / SIZE][x / SIZE] == '1') && x % SIZE != 0 && (cub->angle < 90 || cub->angle > 270))
	// 	return (3);
	// if ((cub->map.map[y / SIZE][x / SIZE] == '1') && x % SIZE != 0 && (cub->angle > 90 && cub->angle < 270))
	// 	return (1);
	// if ((cub->map.map[y / SIZE][x / SIZE] == '1') && y % SIZE != 0 && (cub->angle > 0 && cub->angle < 180))
	// 	return (4);
	// if ((cub->map.map[y / SIZE][x / SIZE] == '1') && y % SIZE != 0 && (cub->angle <= 359 || cub->angle > 180))
	// 	return (2);
	return (0);
}

int abs(int n)
{
	if (n > 0)
		return (n);
	return (-n);
}
 
void dda(t_cub *cub, int x, int y, int color, int ray)
{
	t_pos	delta;
	int		i;
	int 	steps;
	float	fl_x;
	float	fl_y;

	(void)ray;
	delta.x = x - cub->plr.real_x;
	delta.y = y - cub->plr.real_y;
	if (abs(delta.x) > abs(delta.y))
		steps = abs(delta.x);
	else
		steps = abs(delta.y);
	fl_x = cub->plr.real_x;
	fl_y = cub->plr.real_y;
	i = 0;
	while (i++ <= steps)
	{
		cub->rays[ray].face = check_walls(round(fl_x), round(fl_y), cub);
		if (cub->rays[ray].face)
			break ;
		my_mlx_pixel_put(&cub->img_map, round(fl_x), round(fl_y), color);
        fl_x += (delta.x / (float)steps);
        fl_y += (delta.y / (float)steps);
    }
}

float	distance(int x1, int y1, int x2, int y2)
{
	int dx;
    int dy;

    dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(pow(dx, 2) + pow(dy, 2)));
}

float	angle(float a, float b)
{
	float	c;
	float	right;

	right = 90;
	c = (atan(a / b)) * (180 / M_PI);
	if (c < 0)
		c = 360 - c;
	// printf("%f\n", c);
	// printf("A : %f\nB : %f\n", a, b);
	return (right - c);
}

float expand_ray(t_cub *cub, float angle)
{
	double	rad;
    int		i;
	int		x;
	int		y;

	rad = angle * (M_PI / 180);
    i = 0;
    while (1) 
	{
        x = cub->plr.real_x + (i * cos(rad));
        y = cub->plr.real_y + (i * sin(rad));
        if (cub->map.map[y / SIZE][x / SIZE] == '1')
            break ;
		my_mlx_pixel_put(&cub->img_map, round(x) / 4, round(y) / 4, GREEN);
        i++;
    }
	return (distance(cub->plr.real_x, cub->plr.real_y, x, y));
}
