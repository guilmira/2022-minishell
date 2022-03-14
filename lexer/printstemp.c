/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstemp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:49:33 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/14 12:49:57 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	printer(char **table, int *org)
{
	int	i;

	i = -1;
	while (table[++i])
		printf("tabla %i:         _%s_  % 4i\n", i, table[i], org[i]);
	printf("--------------\n");
}
