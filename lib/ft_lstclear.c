/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:41:43 by kadoup            #+#    #+#             */
/*   Updated: 2024/12/29 18:00:39 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		next = tmp->next;
		ft_lstdelone(tmp);
		tmp = next;
	}
	*lst = NULL;
}
