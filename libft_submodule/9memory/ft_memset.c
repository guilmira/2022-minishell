/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 12:34:38 by guilmira          #+#    #+#             */
/*   Updated: 2021/06/22 12:26:21 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : fills reference of memory with CASTED TO CHAR int. [Iterative].
 * 1. Cast reference to an unsigned char pointer for byte to byte access.
 * 2. Advences byte a byte filling the allocated memory with an unsigned char.
 * */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *) b;
	while (i < len)
		ptr[i++] = (unsigned char) c;
	return (b);
}
