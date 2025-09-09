/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:50:02 by kadoup            #+#    #+#             */
/*   Updated: 2025/04/02 14:49:06 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_recurse(unsigned long nb, char *base, int baselen)
{
	if (nb >= baselen)
		ft_putnbr_base_recurse(nb / baselen, base, baselen);
	nb %= baselen;
	nb = base[nb];
	write(1, &nb, 1);
}

void	ft_putnbr_base(unsigned long nb, char *base)
{
	int	i;

	i = ft_strlen(base);
	if (i <= 1)
		return ;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	ft_putnbr_base_recurse(nb, base, i);
}
