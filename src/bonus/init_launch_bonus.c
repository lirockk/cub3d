/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_launch_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:04:44 by ademurge          #+#    #+#             */
/*   Updated: 2023/02/27 11:49:34 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init(t_cub *cub, int ac, char **av)
{
	if (ac != 2)
		ft_error(cub, "Wrong number of arguments.");
	else if (!check_extension(av[1], ".cub"))
		ft_error(cub, "Wrong file extension.");
	cub->txtr.ea = NULL;
	cub->txtr.no = NULL;
	cub->txtr.so = NULL;
	cub->txtr.we = NULL;
	cub->txtr.c = -1;
	cub->txtr.f = -1;
	cub->display_map = 0;
}

void	get_textures_addr(t_text *text)
{
	text->north.addr = mlx_get_data_addr(text->north.img,
			&text->north.bits_per_pixel, &text->north.line_length,
			&text->north.endian);
	text->east.addr = mlx_get_data_addr(text->east.img,
			&text->east.bits_per_pixel, &text->east.line_length,
			&text->east.endian);
	text->south.addr = mlx_get_data_addr(text->south.img,
			&text->south.bits_per_pixel, &text->south.line_length,
			&text->south.endian);
	text->west.addr = mlx_get_data_addr(text->west.img,
			&text->west.bits_per_pixel, &text->west.line_length,
			&text->west.endian);
}

void	init_textures(t_cub *cub, t_text *text)
{
	text->north.img = mlx_new_image(cub->mlx, 256, 256);
	text->east.img = mlx_new_image(cub->mlx, 256, 256);
	text->south.img = mlx_new_image(cub->mlx, 256, 256);
	text->west.img = mlx_new_image(cub->mlx, 256, 256);
	text->north.img = mlx_xpm_file_to_image(cub->mlx, cub->txtr.no,
			&text->north_width, &text->north_height);
	if (!text->north.img)
		ft_error(cub, "Invalid texture file");
	text->east.img = mlx_xpm_file_to_image(cub->mlx, cub->txtr.ea,
			&text->east_width, &text->east_height);
	if (!text->east.img)
		ft_error(cub, "Invalid texture file");
	text->south.img = mlx_xpm_file_to_image(cub->mlx, cub->txtr.so,
			&text->south_width, &text->south_height);
	if (!text->south.img)
		ft_error(cub, "Invalid texture file");
	text->west.img = mlx_xpm_file_to_image(cub->mlx, cub->txtr.we,
			&text->west_width, &text->west_height);
	if (!text->west.img)
		ft_error(cub, "Invalid texture file");
	get_textures_addr(text);
}

void	init_others(t_cub *cub)
{
	cub->map_title.img = mlx_new_image(cub->mlx, 359, 86);
	cub->map_title.img = mlx_xpm_file_to_image(cub->mlx,
			"./files/textures/Map_title2.xpm",
			&cub->map_title_w, &cub->map_title_h);
	cub->map_title.addr = mlx_get_data_addr(cub->map_title.img,
			&cub->map_title.bits_per_pixel, &cub->map_title.line_length,
			&cub->map_title.endian);
	cub->scroll.img = mlx_new_image(cub->mlx, 360, 361);
	cub->scroll.img = mlx_xpm_file_to_image(cub->mlx,
			"./files/textures/Scroll.xpm",
			&cub->scroll_w, &cub->scroll_h);
	cub->scroll.addr = mlx_get_data_addr(cub->scroll.img,
			&cub->scroll.bits_per_pixel, &cub->scroll.line_length,
			&cub->scroll.endian);
}

void	launch(t_cub *cub)
{
	cub->mlx = mlx_init();
	init_textures(cub, &cub->txtr);
	init_others(cub);
	cub->img_map.img = mlx_new_image(cub->mlx, (cub->map.w * SIZE) / MAP_DIV,
			(cub->map.h * SIZE) / MAP_DIV);
	cub->img_map.addr = mlx_get_data_addr(cub->img_map.img,
			&cub->img_map.bits_per_pixel, &cub->img_map.line_length,
			&cub->img_map.endian);
	cub->img_col.img = mlx_new_image(cub->mlx, 1, WIN_HEIGHT);
	cub->img_col.addr = mlx_get_data_addr(cub->img_col.img,
			&cub->img_col.bits_per_pixel, &cub->img_col.line_length,
			&cub->img_col.endian);
	create_window_main(cub);
	mlx_hook(cub->win_game, DESTROY_BUTTON, 0, (void *)ft_close, cub);
	mlx_hook(cub->win_game, KEYPRESS, 0, (void *)deal_key, cub);
	mlx_loop(cub->mlx);
}
