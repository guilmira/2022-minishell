/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:10:34 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/07 11:01:38 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Checks string for desired character. If
 * found a, for example an space, it will return 1. */
static int	check_set(char const c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

/** PURPOSE : Takes a string and trims string set at the beginning and end.
  * 			--ALWAYS ALLOCATES MEMORY (if strings exist)--
 * 1. Fixes counters. this is: 
 * i = first non 'space' found. 
 * j = first non 'space' found, counting from the back.
 * 2. Uses substr(here memory allocation occurs) to create a string
 * that will contain only the desired characters. 
 * The line if (ft_strlen(s1) == 1) is a patch introduced after minishell.
 * It takes into account if a single character is introduced for trimming. */
char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	if (s1 && set)
	{
		j = ft_strlen(s1);
		i = -1;
		while (s1[++i])
			if (check_set(s1[i], set) == 0)
				break ;
		while (--j > 0)
			if (check_set(s1[j], set) == 0)
				break ;
		if (j == 0)
		{
			if (ft_strlen(s1) == 1)
				j++;
			return (ft_substr(s1, i, j));
		}
		return (ft_substr(s1, i, j + 1 - i));
	}
	return (0);
}
