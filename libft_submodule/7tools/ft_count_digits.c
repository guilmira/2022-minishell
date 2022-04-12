/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:55:46 by guilmira          #+#    #+#             */
/*   Updated: 2021/09/13 15:00:16 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : counts digits of an int (iterative) */
int	ft_count_digits(int n)
{
	int	digits;

	digits = 1;
	n /= 10;
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}
