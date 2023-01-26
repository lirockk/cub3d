/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:29:17 by ademurge          #+#    #+#             */
/*   Updated: 2023/01/26 10:54:50 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init(t_cub *cub, int ac, char **av)
{
	if (ac != 2)
		ft_error("Wrong number of arguments.");
	else if (!check_extension(av[1]))
		ft_error("Wrong file extension.");
	cub->txtr.c = NULL;
	cub->txtr.ea = NULL;
	cub->txtr.f = NULL;
	cub->txtr.no = NULL;
	cub->txtr.so = NULL;
	cub->txtr.we = NULL;
}

void	ft_close(int keycode, t_cub *cub)
{
	(void) keycode;
	(void)cub;
	// free_all(cub);
	exit (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void deal_key(int key, t_cub *cub)
{
	if (key == ESC)
	{
		mlx_destroy_window(cub->mlx, cub->win_main);
		mlx_destroy_window(cub->mlx, cub->win_data);
		free (cub->mlx);
		exit(0);
	}
	if (key == W || key == A || key == S || key == D)
		move(cub, key);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate(cub, key);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	init(&cub, ac, av);
	parse(&cub, av[1]);
	cub.mlx = mlx_init();
	cub.img_map.img = mlx_new_image(cub.mlx, cub.map.w * SIZE, cub.map.h * SIZE);
	cub.img_map.addr = mlx_get_data_addr(cub.img_map.img, &cub.img_map.bits_per_pixel, &cub.img_map.line_length,
								&cub.img_map.endian);
	cub.img_game.img = mlx_new_image(cub.mlx, WIN_WIDTH, WIN_HEIGHT);
	cub.img_game.addr = mlx_get_data_addr(cub.img_game.img, &cub.img_game.bits_per_pixel, &cub.img_game.line_length,
								&cub.img_game.endian);
	create_window_main(&cub);
	create_window_data(&cub);
	create_window_game(&cub);
	mlx_hook(cub.win_main, 17, 0, (void *)ft_close, &cub);
	mlx_hook(cub.win_game, KEYPRESS, 0, (void *)deal_key, &cub);
	// mlx_put_image_to_window(cub.mlx, cub.win_main, cub.img.img, 0, 0);
	// mlx_mouse_hook(cub.win_main, (void *)click, &cub);
	mlx_loop(cub.mlx);
	// free_all(&cub);
	// return (0);
}
