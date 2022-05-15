/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 07:44:40 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/24 07:52:29 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : frees spaces allocated for any string table. */
void	ft_free_split(char **table)
{
	int	w;

	w = -1;
	if (table)
	{
		while (table[++w])
		{
			free(table[w]);
			table[w] = NULL;
		}
		free(table);
		table = NULL;
	}
}
