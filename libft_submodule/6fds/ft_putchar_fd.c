/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 08:41:59 by guilmira          #+#    #+#             */
/*   Updated: 2021/09/12 15:58:01 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Prints char to file/ std output(fd = 1). */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}
