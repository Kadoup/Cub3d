/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:18:43 by tjourdan          #+#    #+#             */
/*   Updated: 2024/11/15 15:14:51 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_len(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			count;
	long int	num;
	char		*dest;
	int			i;

	num = n;
	count = count_len(num);
	i = 0;
	dest = malloc(count + 1);
	if (!dest)
		return (NULL);
	if (num < 0)
	{
		num = -num;
		dest[0] = '-';
		i++;
	}
	dest[count] = '\0';
	while (count > i)
	{
		count--;
		dest[count] = (num % 10) + '0';
		num /= 10;
	}
	return (dest);
}
