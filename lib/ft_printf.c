/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:55:33 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/09 17:45:08 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LWR "0123456789abcdef"

#define UPR "0123456789ABCDEF"

int	parse(const char *format, va_list arg)
{
	if (*format == '%')
	{
		format++;
		if (*format == 'd' || *format == 'i')
			return (putnbrint(va_arg(arg, int)));
		else if (*format == 'u')
			return (putunbrint(va_arg(arg, unsigned int)));
		else if (*format == '%')
			return (putcharint('%'));
		else if (*format == 'c')
			return (putcharint((char)va_arg(arg, int)));
		else if (*format == 's')
			return (putstrint(va_arg(arg, char *)));
		else if (*format == 'x')
			return (putnbr_baseint(va_arg(arg, unsigned int), LWR));
		else if (*format == 'X')
			return (putnbr_baseint(va_arg(arg, unsigned int), UPR));
		else if (*format == 'p')
			return (putptr(va_arg(arg, void *)));
	}
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		count;
	int		j;

	i = 0;
	j = 0;
	count = 0;
	va_start(arg, format);
	while (format[i])
	{
		j = parse(&format[i], arg);
		if (j == -1)
			j = putcharint(format[i]);
		else
			i++;
		count += j;
		i++;
	}
	va_end(arg);
	return (count);
}
