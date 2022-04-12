/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:51:30 by guilmira          #+#    #+#             */
/*   Updated: 2021/07/24 10:35:45 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : returns address of the last element.
 * 1. While the NEXT element is pointing somewhere (i.e. not NULL) \
 * LIST is updated and then returned
 * Note than in the main program, list will not be updated,
 * the function will only return a new adress, but not replace it. */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
