/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:29:17 by ademurge          #+#    #+#             */
/*   Updated: 2023/01/27 16:13:24 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_corner(int x, int y)
{
	if (!(y % SIZE) && !(x % SIZE))
		return (1);
	else if (!(y % SIZE) && !((x + 1) % SIZE))
		return (2);
	else if (!(x % SIZE) && !((y + 1) % SIZE))
		return (3);
	else if (!((x + 1) % SIZE) && !((y + 1) % SIZE))
		return (4);
	return (0);
}

// int	get_side(float x, float y, int corner)
// {
// 	float	x_dec;
// 	float	y_dec;

// 	printf("x : %f | y : %f\n", x, y);
// 	x_dec = x - floorf(x);
// 	y_dec = y - floorf(y);
// 	if (corner == 1)
// 	{
// 		if (x_dec > y_dec)
// 			return (WEST);
// 		return (NORTH);
// 	}
// 	else if (corner == 2)
// 	{
// 		if ((floorf(x) + 1) - x_dec > y_dec)
// 			return (EAST);
// 		return (NORTH);
// 	}
// 	else if (corner == 3)
// 	{
// 		if ((floorf(y) + 1) - y_dec > x_dec)
// 			return (SOUTH);
// 		return (WEST);
// 	}
// 	if ((floorf(x) + 1) - x_dec > (floorf(y) + 1) - y_dec)
// 		return (SOUTH);
// 	return (EAST);
// }

// void	display_wall(int side)
// {
// 	if (side == 1)
// 		printf("NORTH\n");
// 	else if (side == 2)
// 		printf("EAST\n");
// 	else if (side == 3)
// 		printf("SOUTH\n");
// 	else if (side == 4)
// 		printf("WEST\n");
// }

int	check_walls(t_vector plr, float x, float y)
{
	int	corner;
	// int side;

	corner = is_corner(x, y);
	if (corner == 1)
		return (north_west(plr, x, y));
	else if (corner == 2)
		return (north_east(plr, x, y));
	else if (corner == 3)
		return (south_west(plr, x, y));
	else if (corner == 4)
		return (south_east(plr, x, y));
	if (!((int)y % SIZE))
		return (NORTH);
	else if (!((int)x % SIZE))
		return (WEST);
	else if (!((int)(x + 1) % SIZE))
		return (EAST);
	return (SOUTH);
	// if (cub->map.map[y / SIZE][x / SIZE] == '1')
	// {
	// 	if (!(x % SIZE) && !(y % SIZE))
	// 		return (5);
	// 	if (cub->angle >= 270.00000000 && cub->angle <= 360.00000000)
	// 	{
	// 		if (!(x % SIZE))
	// 			return (WEST);
	// 		else if (!((y + 1) % SIZE))
	// 			return (SOUTH);
	// 	}
	// 	if (cub->angle >= 180.00000000 && cub->angle <= 270.00000000)
	// 	{
	// 		if (!((x + 1) % SIZE))
	// 			return (EAST);
	// 		else if (!((y + 1) % SIZE))
	// 			return (SOUTH);
	// 	}
	// 	if (cub->angle >= 90.00000000 && cub->angle <= 180.00000000)
	// 	{
	// 		if (!((x + 1) % SIZE))
	// 			return (EAST);
	// 		else if (!(y % SIZE))
	// 			return (NORTH);
	// 	}
	// 	if (cub->angle >= 0.00000000 && cub->angle <= 90.00000000)
	// 	{
	// 		if (!(x % SIZE))
	// 			return (WEST);
	// 		else if (!(y % SIZE))
	// 			return (NORTH);
	// 	}
	// }
	// return (0);
}

int abs(int n)
{
	if (n > 0)
		return (n);
	return (-n);
}

// void dda(t_cub *cub, int x, int y, int color, int ray)
// {
// 	t_pos	delta;
// 	int		i;
// 	int 	steps;
// 	float	fl_x;
// 	float	fl_y;

// 	(void)ray;
// 	delta.x = x - cub->plr.real_x;
// 	delta.y = y - cub->plr.real_y;
// 	if (abs(delta.x) > abs(delta.y))
// 		steps = abs(delta.x);
// 	else
// 		steps = abs(delta.y);
// 	fl_x = cub->plr.real_x;
// 	fl_y = cub->plr.real_y;
// 	i = 0;
// 	while (i++ <= steps)
// 	{
// 		cub->rays[ray].face = check_walls(round(fl_x), round(fl_y), cub);
// 		if (cub->rays[ray].face)
// 			break ;
// 		my_mlx_pixel_put(&cub->img_map, round(fl_x), round(fl_y), color);
//         fl_x += (delta.x / (float)steps);
//         fl_y += (delta.y / (float)steps);
//     }
// }

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
	return (right - c);
}

void dda(t_cub *cub, t_ray *ray)
{
	double	rad;
	int		i;
	float	x;
	float	y;

	rad = cub->angle * (M_PI / 180);
	i = 0;
	while (1)
	{
		x = ray->real_x + (i * cos(rad));
		y = ray->real_y + (i * sin(rad));
		if (cub->map.map[(int)y / SIZE][(int)x / SIZE] == '1')
		{
			ray->face = check_walls(cub->plr, x, y);
			ray->l = distance(ray->real_x, ray->real_y, x, y);
			break ;
		}
		i++;
	}
}

void expand_ray(t_cub *cub, t_ray *ray)
{
	double	rad;
	int		i;
	float	x;
	float	y;

	rad = ray->angle * (M_PI / 180);
	i = 0;
	while (1)
	{
		x = cub->plr.real_x + (i * cos(rad));
		y = cub->plr.real_y + (i * sin(rad));
		if (cub->map.map[(int)y / SIZE][(int)x / SIZE] == '1')
		{
			ray->real_x = roundf(x);
			ray->real_y = roundf(y);
			ray->face = check_walls(cub->plr, x, y);
			ray->l = distance(cub->plr.real_x, cub->plr.real_y, x, y);
			break ;
		}
		my_mlx_pixel_put(&cub->img_map, round(x) / 4, round(y) / 4, GREEN);
		i++;
	}
}
