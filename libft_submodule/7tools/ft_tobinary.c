/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tobinary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 11:17:35 by guilmira          #+#    #+#             */
/*   Updated: 2021/09/23 12:56:37 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : writes binary in allocated memory [recursive].
 * 1. A static int variable is defined. It will maintain its value.
 * 2. If the number is not a single digit, recurssion.
 * 3. It will eventually reach the first digit. (from 643, it will get to '6')
 * 4. Converts the first digit to a binary char in position i = 0;
 * 5. Converts the rest of the digits in position i = 1, i = 2...
 * 6. Always closes the string by adding a 0 at the last position. */
static void	binary_writer(int n, char *ptr)
{
	static int	i;

	if (n / 2)
		binary_writer(n / 2, ptr);
	else
	{
		i = 0;
		if (n < 0)
		{
			ptr[0] = '-';
			i++;
		}
	}
	ptr[i++] = '0' + n % 2;
	ptr[i] = '\0';
}

/** PURPOSE : converts integer into its binary string equivalent.
 * 						--ALLOCATES MEMORY--
 * 1. Allocate enough memory to contain enough digits. Note how it allocates
 * extra space in order to be able to finish the string with the '\0'
 * and also in case the number is negative and needs a '-' char.
 * 2. Write binary digits as a string using recurssive funct-writer. */
char	*ft_tobinary(int n)
{
	char	*ptr;

	ptr = ft_calloc(ft_count_digits_base(n, 2) + 2, sizeof(char));
	binary_writer(n, ptr);
	return (ptr);
}
