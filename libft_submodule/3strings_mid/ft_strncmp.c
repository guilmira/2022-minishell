/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:55:44 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/06 15:19:09 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
/** PURPOSE : compares string difference up to n char.
 * EXAMPLE1 --  ft_strncmp("lex_PIPE", "lex_", 4)) 
 * -> Return 0, as it evaluates 4 characters
 * EXAMPLE2 -- ft_strncmp("lex1PIPE", "lex0", 4)
 * -> Return 1, the diff on the fourth char */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
