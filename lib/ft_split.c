/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadoup <kadoup@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:45:08 by kadoup            #+#    #+#             */
/*   Updated: 2024/11/23 19:51:05 by kadoup           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_substr(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		count++;
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (count);
}

size_t	substrlen(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != c)
	{
		j++;
		i++;
	}
	return (j);
}

char const	*fill_tab(char const *s, char c, char **res, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*res = malloc(len + 1);
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		(*res)[j] = s[i];
		i++;
		j++;
	}
	(*res)[j] = '\0';
	return (s + i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**res;
	int		len;

	count = count_substr(s, c);
	i = 0;
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	while (i < count)
	{
		len = substrlen(s, c);
		s = fill_tab(s, c, &res[i], len);
		i++;
	}
	res[i] = 0;
	return (res);
}
