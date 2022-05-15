/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:24:28 by guilmira          #+#    #+#             */
/*   Updated: 2021/09/23 07:44:09 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : find any of the letters if located in origin string.
 * 1. Searchs str character by character.
 * 2. If letter is located, returns address to the letter (included). */
char	*ft_strchr_plus(char *str, char *letters)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (letters[++j])
		{
			if (str[i] == letters[j])
				return (&str[i]);
		}
	}
	if (!letters)
		return (&str[i]);
	return (NULL);
}
