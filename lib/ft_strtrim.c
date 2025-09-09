/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:25:02 by tjourdan          #+#    #+#             */
/*   Updated: 2024/11/15 15:15:40 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char c, const char *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;
	char	*res;
	size_t	i;

	if (!s1 || !set || (!s1 && !set))
		return (0);
	s = 0;
	e = ft_strlen(s1);
	while (s1[s] && check_set(s1[s], set))
		s++;
	while (e > s && check_set(s1[e - 1], set))
		e--;
	res = malloc(sizeof(char) * (e - s + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < e - s)
	{
		res[i] = s1[s + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
