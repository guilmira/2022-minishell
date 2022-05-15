/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:32:55 by guilmira          #+#    #+#             */
/*   Updated: 2021/05/30 16:35:16 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source_aux;
	unsigned char	*destino_aux;
	size_t			i;

	source_aux = (unsigned char *) src;
	destino_aux = (unsigned char *) dst;
	i = -1;
	if (source_aux == destino_aux)
		return (source_aux);
	else if (destino_aux > source_aux)
	{
		while (len)
		{
			destino_aux[len - 1] = source_aux[len - 1];
			len--;
		}
	}
	else
		while (++i < len)
			destino_aux[i] = source_aux[i];
	return (dst);
}
