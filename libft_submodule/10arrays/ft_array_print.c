/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:39:46 by guilmira          #+#    #+#             */
/*   Updated: 2021/07/20 12:57:10 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Prints each element of vector.
 * Note: The function is designed to work not only with static arrays,
 * but also with pointers allocated with malloc. That´s the reason why
 * int size MUST be an input argument.
 * int n = sizeof(array)/sizeof(array[0]) only works with static array.
*/
void	ft_array_print(int *array, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		ft_putnbr_fd(array[i], 1);
		ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
}
