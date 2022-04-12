/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 13:31:46 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/12 11:37:34 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : compares character by character until string end.
 * 1. Returns 0 in case of matching strings.
 * 2. Returns diff of characters if strings do not match. 
 * IMPORTANT - The order of the strings matters. */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
	{
		if (s1[i] != s2[i] || !s1[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	}
	return (0);
}
