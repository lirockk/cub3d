/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:24:27 by ademurge          #+#    #+#             */
/*   Updated: 2023/02/27 14:31:04 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	return_atoi(unsigned long long sum, int sign, int size)
{
	unsigned long long	max;

	max = 9223372036854775807U;
	if (((sum > max) || size > 19) && sign > 0)
		return (-1);
	else if (((sum > (max + 1)) || size > 19) && sign < 0)
		return (0);
	return (sum * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long	sum;
	int					sign;
	int					i;
	int					size;

	size = 0;
	sum = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && ++size)
		sum = sum * 10 + str[i++] - 48;
	if (str[i])
		return (-1);
	return (return_atoi(sum, sign, size));
}
