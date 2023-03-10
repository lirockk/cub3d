/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:23:58 by ademurge          #+#    #+#             */
/*   Updated: 2023/02/27 14:15:49 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_good_coord(char c)
{
	if (c == '0' || c == '1' || ft_strchr(POS_CHAR, c))
		return (1);
	return (0);
}

int	check_zero(char **map, int i, int j)
{
	if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1])
		return (0);
	if (!is_good_coord(map[i - 1][j - 1]))
		return (0);
	if (!is_good_coord(map[i - 1][j]))
		return (0);
	if (!is_good_coord(map[i - 1][j + 1]))
		return (0);
	if (!is_good_coord(map[i][j - 1]))
		return (0);
	if (!is_good_coord(map[i][j + 1]))
		return (0);
	if (!is_good_coord(map[i + 1][j - 1]))
		return (0);
	if (!is_good_coord(map[i + 1][j]))
		return (0);
	if (!is_good_coord(map[i + 1][j + 1]))
		return (0);
	return (1);
}

void	init_plr(t_cub *cub, int x, int y, char cardinal)
{
	int		i;
	char	*dir;

	cub->plr.x = x;
	cub->plr.y = y;
	i = -1;
	dir = POS_CHAR;
	while (dir[++i])
	{
		if (cardinal == dir[i])
			cub->angle = 90 * i;
	}
	cub->plr.real_x = (x * SIZE) + (SIZE / 2);
	cub->plr.real_y = (y * SIZE) + (SIZE / 2);
}

static int	check_one(t_cub *cub, int y, int x)
{
	char	**map;

	map = cub->map.map;
	if (x > 0 && is_good_coord(map[y][x - 1]))
		return (1);
	if (is_good_coord(map[y][x + 1]))
		return (1);
	if (y < cub->map.h - 1 && is_good_coord(map[y + 1][x]))
		return (1);
	if (y > 0 && is_good_coord(map[y - 1][x]))
		return (1);
	return (0);
}

int	check_map(t_cub *cub, char **map)
{
	int	i;
	int	j;
	int	pos;

	i = -1;
	pos = 0;
	while (map[++i] && pos <= 1)
	{
		j = -1;
		while (map[i][++j] && pos <= 1)
		{
			if (ft_strchr(POS_CHAR, map[i][j]))
				init_plr(cub, j, i, map[i][j]);
			if (map[i][j] == '0' && !check_zero(cub->map.map, i, j))
				ft_error(cub, "Map must be surrounded by walls");
			if (map[i][j] == '1' && !check_one(cub, i, j))
				ft_error(cub, "Map must be surrounded by walls");
			if (ft_strchr(POS_CHAR, map[i][j]))
				pos++;
		}
	}
	if (!pos || pos > 1)
		ft_error(cub, "There must be one player on the map.");
	return (1);
}
