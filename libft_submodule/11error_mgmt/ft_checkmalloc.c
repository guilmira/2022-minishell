/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmalloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:29:07 by guilmira          #+#    #+#             */
/*   Updated: 2022/04/10 11:49:18 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Light version of a malloc check that shutdowns
 * program + clears memory heap. 
 * Check whether mem-alloc proceeds successfully. */
int	ft_checkmalloc(void *ptr, char *str)
{
	if (ptr == NULL)
	{
		ft_shut(str);
		return (1);
	}
	else
		return (0);
}
