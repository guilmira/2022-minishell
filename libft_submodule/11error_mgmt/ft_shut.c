/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 11:40:20 by guilmira          #+#    #+#             */
/*   Updated: 2022/04/10 11:49:52 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Shuts program with an output message.
  * 					--Uses exit function-- 
 * Reference: The function ft_shutdown, is intended
 * to be the equivalent to ft_shut. It also clears memory, hence
 * in needs an additional parameter: ft_shutdow(str, PROGRAM); 
 * Error parameter can be substituted by macro. */
void	ft_shut(char *str)
{
	int	error_parameter;

	error_parameter = 2;
	ft_senderror(str);
	exit(error_parameter);
}
