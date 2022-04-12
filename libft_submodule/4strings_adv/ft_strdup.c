/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:04:36 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/23 15:10:25 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Duplicates input string by allocating memory at the heap.
  * 					--ALLOCATES MEMORY--
 * 1. Allocates enough memory by using string lenght (+ 1 to account for \\0).
 * 2. Copies string, then adds 0. Returns pointer. */
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = -1;
	ptr = ft_calloc(1 + ft_strlen(s1), sizeof(*ptr));
	if (!ptr)
		return (NULL);
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}
