/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:09:17 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/23 15:16:20 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Joins two strings into a new allocated string.
  * 					--ALLOCATES MEMORY--
 * 1. Allocates enough memory by adding the two lenghts (+ 1 to account for \\0).
 * 2. Copies both strings adjacent, then adds 0. Returns pointer. 
 * 3. Does not free original strings. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s2 || !s1)
		return (0);
	ptr = (char *) ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(*ptr));
	if (!ptr)
		return (NULL);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	j = -1;
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}
