/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:15:29 by guilmira          #+#    #+#             */
/*   Updated: 2021/05/30 10:59:52 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src_aux;
	size_t			i;

	i = 0;
	src_aux = (unsigned char *) s;
	while (i < n)
	{
		if (src_aux[i] == (unsigned char) c)
			return (&src_aux[i]);
		i++;
	}
	return (NULL);
}
