/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:14:38 by guilmira          #+#    #+#             */
/*   Updated: 2021/05/30 16:23:20 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_aux;
	unsigned char	*s2_aux;
	size_t			i;

	s1_aux = (unsigned char *) s1;
	s2_aux = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1_aux[i] != s2_aux[i])
			return (s1_aux[i] - s2_aux[i]);
		i++;
	}
	return (0);
}
