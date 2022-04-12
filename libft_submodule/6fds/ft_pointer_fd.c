/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:19:51 by guilmira          #+#    #+#             */
/*   Updated: 2021/06/21 15:59:52 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** Pendiente de revisar **/
void	ft_pointer_fd(unsigned long long n, char *base, int fd)
{
	int					i;
	unsigned long long	x;

	i = -1;
	if (!base || !base[0])
		return ;
	while (base[++i])
		if (ft_strchr(base + 1 + i, base[i]) || \
		ft_strchr(base, '+') || ft_strchr(base, '-'))
			return ;
	x = n;
	if (x / ft_strlen(base) == 0)
		ft_putchar_fd(base[x % ft_strlen(base)], fd);
	else
	{
		ft_pointer_fd(x / ft_strlen(base), base, fd);
		ft_putchar_fd(base[x % ft_strlen(base)], fd);
	}
}
