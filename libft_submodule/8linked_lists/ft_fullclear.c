/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fullclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:54:13 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/22 09:24:57 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : clears linked list from first element to last, including content
 * Its important to remember that all elements of content of the
 * list must be allocated. */
void	ft_fullclear(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = tmp;
	}
}
