/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:19:26 by guilmira          #+#    #+#             */
/*   Updated: 2021/09/23 11:24:41 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : writes integer in allocated memory [recursive].
 * 1. A static int variable is defined. It will maintain its value.
 * 2. If the number is not a single digit, recurssion.
 * 3. It will eventually reach the first digit. (from 643, it will get to '6')
 * 4. Converts the first digit to a string in position i = 0;
 * 5. Converts the rest of the digits in position i = 1, i = 2...
 * 6. Always closes the string by adding a 0 at the last position. */
static void	itoa_writer(int n, char *ptr)
{
	static int	i;

	if (n / 10)
		itoa_writer(n / 10, ptr);
	else
	{
		i = 0;
		if (n < 0)
			ptr[i++] = '-';
	}
	if (n < 0)
		n *= -1;
	ptr[i] = '0' + n % 10;
	ptr[++i] = '\0';
}

/** PURPOSE : converts integer into its string equivalent.
 * 1. Allocates memory in heap. Note how it allocates 2 extra space
 * in order to be able to finish the string with the '\0' and also
 * in case the number is negative and needs a '-' char.
 * 2. Calls recursive function itoa-writer. */
char	*ft_itoa(int n)
{
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ptr = ft_calloc(ft_count_digits(n) + 2, sizeof(char));
	if (!ptr)
		return (NULL);
	itoa_writer(n, ptr);
	return (ptr);
}
