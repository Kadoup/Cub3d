/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:09:33 by tjourdan          #+#    #+#             */
/*   Updated: 2025/04/02 14:54:28 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list	**res)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *res;
	tmp2 = (*res)->next;
	if (tmp2->next == NULL)
	{
		tmp->next = NULL;
		tmp2->next = tmp;
		*res = tmp2;
	}
	else
	{
		tmp->next = tmp2->next;
		tmp2->next = tmp;
		*res = tmp2;
	}
}

void	ft_lstpush(t_list **fromlist, t_list **tolist)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *fromlist;
	tmp2 = tmp->next;
	ft_lstadd_front(tolist, ft_lstnew(tmp->value));
	ft_lstdelone(*fromlist);
	*fromlist = tmp2;
}

void	ft_lstrotate(t_list **list)
{
	t_list	*current;
	t_list	*next;
	t_list	*last;

	current = *list;
	next = current->next;
	last = ft_lstlast(*list);
	last->next = current;
	current->next = NULL;
	*list = next;
}

void	ft_lstrrotate(t_list **list)
{
	t_list	*current;
	t_list	*last;
	t_list	*prevlast;

	current = *list;
	last = ft_lstlast(*list);
	prevlast = ft_lstprevlast(*list);
	last->next = current;
	prevlast->next = NULL;
	*list = last;
}
