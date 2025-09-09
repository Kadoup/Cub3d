/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:55:04 by kadoup            #+#    #+#             */
/*   Updated: 2025/04/02 14:49:51 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, int (*f)(int))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*res;
	int		content;

	tmp = lst;
	res = NULL;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		content = (*f)(tmp->value);
		new = ft_lstnew(content);
		if (new)
			ft_lstadd_back(&res, new);
		tmp = tmp->next;
	}
	return (res);
}
