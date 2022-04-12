/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 11:16:21 by guilmira          #+#    #+#             */
/*   Updated: 2021/09/23 11:16:37 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : counts digits of an int (iterative)
 * Base might be binary, decimal, hexadecimal... */
int	ft_count_digits_base(int n, int base)
{
	int	digits;

	digits = 1;
	n /= base;
	while (n)
	{
		digits++;
		n /= base;
	}
	return (digits);
}
