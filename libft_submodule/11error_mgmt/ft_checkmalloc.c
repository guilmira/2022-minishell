/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmalloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:29:07 by guilmira          #+#    #+#             */
/*   Updated: 2021/09/24 11:31:09 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Check whether mem-alloc proceeds successfully. */
void	ft_checkmalloc(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("Error in memory allocation\n", 1);
		exit(1);
	}
}
