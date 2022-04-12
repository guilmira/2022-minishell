/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 12:47:40 by guilmira          #+#    #+#             */
/*   Updated: 2021/06/22 12:23:27 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : fills reference with zeros.
 * 1. Uses memset with '0' input over 'n' bytes
 * */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
