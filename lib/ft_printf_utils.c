/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:55:48 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/09 17:45:15 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putunbrint(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
	{
		count += putunbrint(nb / 10);
	}
	nb %= 10;
	nb += 48;
	write(1, &nb, 1);
	count++;
	return (count);
}

int	putnbrint(int nb)
{
	int	count;

	count = 0;
	if (nb == INT_MIN)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		count += putcharint('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		count += putnbrint(nb / 10);
	}
	nb %= 10;
	nb += 48;
	count++;
	write(1, &nb, 1);
	return (count);
}

int	putnbr_base_recurse(unsigned long nb, char *base, unsigned int baselen)
{
	int	count;

	count = 0;
	if (nb >= baselen)
		count += putnbr_base_recurse(nb / baselen, base, baselen);
	nb %= baselen;
	nb = base[nb];
	write(1, &nb, 1);
	count++;
	return (count);
}

int	putnbr_baseint(unsigned long nb, char *base)
{
	int	i;
	int	count;

	count = 0;
	i = ft_strlen(base);
	count += putnbr_base_recurse(nb, base, i);
	return (count);
}
