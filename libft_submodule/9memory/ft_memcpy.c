/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:12:10 by guilmira          #+#    #+#             */
/*   Updated: 2021/05/30 16:25:00 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest_aux;
	unsigned char	*src_aux;
	size_t			i;

	dest_aux = (unsigned char *) dst;
	src_aux = (unsigned char *) src;
	i = 0;
	if (!src && !dst)
		return (NULL);
	while (i < n)
	{
		dest_aux[i] = src_aux[i];
		i++;
	}
	return (dest_aux);
}
