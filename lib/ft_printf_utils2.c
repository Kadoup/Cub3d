/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:54:36 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/09 17:47:24 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putcharint(char c)
{
	return (write(1, &c, 1));
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

int	putstrint(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

int	putptr(void *p)
{
	if (!p)
		return (write(1, "(nil)", 5));
	putstrint("0x");
	return (putnbr_baseint((unsigned long)p, "0123456789abcdef") + 2);
}
