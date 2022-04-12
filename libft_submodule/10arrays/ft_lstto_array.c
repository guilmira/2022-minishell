/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstto_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:36:58 by guilmira          #+#    #+#             */
/*   Updated: 2021/08/13 11:05:24 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : allows to refer to structure ptr, returns int */
static int	convert(int *ptr)
{
	return (*ptr);
}

/** PURPOSE : Turns linked list into an array. Returns number of elements.
 * Note 1: DOES NOT FREE MEMORY.
 * Note 2: Is FUNDAMENTAL to store the number of allocated
 * integers, since otherwise it cannot be calculated.
 * A malloc pointer (dynamic allocation) is different from an array
 * and therefore sizeof(array)/ sizeof(array[0]) will not work. */
int	*ft_lstto_array(t_list *list, int *array_size)
{
	int		list_size;
	int		*array;
	int		i;

	list_size = ft_lstsize(list);
	array = ft_calloc(list_size, sizeof(int));
	if (!array)
		return (NULL);
	i = -1;
	while (++i < list_size)
	{
		array[i] = convert(list->content);
		list = list->next;
	}
	*array_size = i;
	return (array);
}
