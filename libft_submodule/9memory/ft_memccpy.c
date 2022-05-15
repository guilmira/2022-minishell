/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:32:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/06/15 17:01:05 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest_aux;
	unsigned char	*src_aux;
	size_t			i;

	dest_aux = (unsigned char *) dst;
	src_aux = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		dest_aux[i] = src_aux[i];
		if (src_aux[i] == (unsigned char) c)
			return (&dest_aux[i + 1]);
		i++;
	}
	return (0);
}
