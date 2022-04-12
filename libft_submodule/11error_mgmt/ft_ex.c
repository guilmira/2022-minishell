/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:24:32 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/06 10:45:01 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Output error with value 1, close the program.
 * Exit signal is 0, to prevent message "make: *** [exe] Error 1"
 * from appearing on screen. */
void	ft_ex(void)
{
	ft_putstr_fd("Exiting program.\n", 1);
	exit(0);
}
