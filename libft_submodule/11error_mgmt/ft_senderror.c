/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_senderror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 11:35:00 by guilmira          #+#    #+#             */
/*   Updated: 2022/04/10 11:52:47 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Outputs error message in STDOUT. 
 * This is fd = 2. */
void	ft_senderror(char *str)
{
	write(2, str, ft_strlen(str));
}
