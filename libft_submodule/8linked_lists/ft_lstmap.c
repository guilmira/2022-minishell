/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:43:29 by guilmira          #+#    #+#             */
/*   Updated: 2021/05/31 11:42:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_node;
	t_list	*first_node;

	if (!lst || !f)
		return (NULL);
	tmp = lst;
	first_node = ft_lstnew(f(tmp->content));
	if (!first_node)
		return (NULL);
	tmp = tmp->next;
	while (tmp)
	{
		new_node = ft_lstnew(f(tmp->content));
		if (!new_node)
		{
			ft_lstclear(&first_node, del);
			return (NULL);
		}
		ft_lstadd_back(&first_node, new_node);
		tmp = tmp->next;
	}
	return (first_node);
}
