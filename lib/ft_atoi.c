/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:44:16 by kadoup            #+#    #+#             */
/*   Updated: 2025/04/02 14:49:19 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *mess)
{
	ft_putstr_fd(mess, 2);
	exit (1);
}

long	ft_atoi(const char *str)
{
	long		sign;
	int			i;
	long		res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		ft_error("please put valide numbers\n");
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - 48);
	if (str[i] && !(str[i] > '0' && str[i] < '9'))
		ft_error("please put valide numbers\n");
	return (res * sign);
}
