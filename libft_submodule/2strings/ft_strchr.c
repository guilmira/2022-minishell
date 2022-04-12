/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:15:26 by guilmira          #+#    #+#             */
/*   Updated: 2021/07/16 14:44:26 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : find letter located in origin string.
 * 1. If letter is located, returns address to the letter (included). */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((char) c == s[i])
			return ((char *) &s[i]);
	}
	if (!c)
		return ((char *) &s[i]);
	return (NULL);
}

/* For the function to work with '\0', it needs to return the position of the
 * string where the \0 is located. This is, the exact adress, so return NULL
 * upon finding !c would not work. */
