/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:29:17 by ademurge          #+#    #+#             */
/*   Updated: 2023/02/06 16:57:08 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_col(t_cub *cub, t_ray ray, int col, t_img *img, int color)
{
	int		ints[2];
	float	height;
	float	line;
	int		*pix;
	float	multi;

	(void)color;
	ints[0] = -1;
	while (++ints[0] < WIN_HEIGHT / 2)
		my_mlx_pixel_put(&cub->img_col, 0, ints[0], CEILING);
	while (++ints[0] < 768)
		my_mlx_pixel_put(&cub->img_col, 0, ints[0], FLOOR);
	height = ((SIZE * SIZE) / floorf(ray.l)) * 25;
	multi = 256.000 / height;
	ints[0] = (768.000 - (int)floorf(height)) / 2;
	ints[1] = ints[0];
	line = 0;
	while (++ints[1] < (768.000 - ints[0]))
	{
		pix = (int*)img->addr + ((int)floorf(line / multi) * (img->line_length / 4) + (int)floorf(ray.col) * (img->bits_per_pixel / 32));
		my_mlx_pixel_put(&cub->img_col, 0, ints[1], mlx_get_color_value(cub->mlx, *pix));
		line += 1.000;
	}
	mlx_put_image_to_window(cub->mlx, cub->win_game, cub->img_col.img, col, 0);
}

void	get_color(t_cub *cub, t_ray ray, int col)
{
	if (ray.side == NORTH)
		draw_col(cub, ray, col, &cub->txtr.north, BLUE);
	else if (ray.side == SOUTH)
		draw_col(cub, ray, col, &cub->txtr.south, DARK_GREEN);
	else if (ray.side == EAST)
		draw_col(cub, ray, col, &cub->txtr.east, DARK_RED);
	else if (ray.side == WEST)
		draw_col(cub, ray, col, &cub->txtr.west, BLACK);
}

void	draw_game(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < NB_RAYS)
		get_color(cub, cub->rays[i], i);
	// draw_cursor(cub);
}

void	init_draw(t_cub *cub)
{
	int	x;
	int	y;

	y = (WIN_HEIGHT / 2) - 1;
	while (--y >= 0)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			my_mlx_pixel_put(&cub->img_game, x, y, cub->txtr.c);
	}
	y = (WIN_HEIGHT / 2) - 1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			my_mlx_pixel_put(&cub->img_game, x, y, cub->txtr.f);
	}
}

void	fish_eye_corr(t_cub *cub, t_ray *ray)
{
	float	cos_a;
	float	radian[2];

	radian[0] = ray->angle * (M_PI / 180);
	radian[1] = cub->angle * (M_PI / 180);
	cos_a = cos(radian[0] - radian[1]);
	ray->l *= cos_a;
}

void	draw(t_cub *cub)
{
	int		i;

	i = -1;
	init_draw(cub);
	cub->rays[MID_RAY] = intersection(cub->plr.real_x, cub->plr.real_y, cub->r, cub->angle);
	cub->rays[MID_RAY].angle = cub->angle;
	expand_ray(cub, &cub->rays[MID_RAY]);
	while (++i < MID_RAY)
	{
		cub->rays[i] = intersection(cub->rays[MID_RAY].real_x, cub->rays[MID_RAY].real_y, (cub->plane / (MID_RAY)) * (MID_RAY - i), cub->angle - 90);
		cub->rays[i].angle = cub->angle - angle(SIZE, (cub->plane / MID_RAY) * (MID_RAY - i));
		if (cub->rays[i].angle < 0)
			cub->rays[i].angle = 360 + cub->rays[i].angle;	
		expand_ray(cub, &cub->rays[i]);
		fish_eye_corr(cub, &cub->rays[i]);
	}
	while (++i < NB_RAYS)
	{
		cub->rays[i] = intersection(cub->rays[MID_RAY].real_x, cub->rays[MID_RAY].real_y, (cub->plane / MID_RAY) * (i - MID_RAY), cub->angle + 90);
		cub->rays[i].angle = cub->angle + angle(SIZE, (cub->plane / MID_RAY) * (i - MID_RAY));
		if (cub->rays[i].angle >= 360)
			cub->rays[i].angle -= 360;
		expand_ray(cub, &cub->rays[i]);
		fish_eye_corr(cub, &cub->rays[i]);
	}
	draw_game(cub);
}
