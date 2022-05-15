/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:08:32 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/16 09:04:23 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Allocates space and copies 's' form 'start' to 'len'.
 * 						--ALLOCATES MEMORY--
 * 1. Mem allocation. If string is smaller than len, then allocate for strlen.
 * Otherwise, only size of len is needed in heap, + 1 to add the /0.
 * 2. Copies content of string and returns it. 
 * Note: if start is bigger than strlen, it still allocates memory for 
 * a string even if it will contain no caracter. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;

	if (!s)
		return (0);
	if ((ft_strlen(s) + 1) < len)
		ptr = (char *) ft_calloc((ft_strlen(s) + 1), sizeof(*ptr));
	else
		ptr = (char *) ft_calloc((len + 1), sizeof(*ptr));
	if (!ptr)
		return (NULL);
	if (start > ft_strlen(s))
	{
		*ptr = 0;
		return (ptr);
	}
	i = 0;
	while (s[i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
