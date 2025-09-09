/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprevlast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:11 by tjourdan          #+#    #+#             */
/*   Updated: 2025/04/02 14:50:06 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstprevlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}
