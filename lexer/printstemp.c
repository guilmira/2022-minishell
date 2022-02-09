/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstemp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:49:33 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/09 08:59:24 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printer(char **table, int *org)
{
	int i;

	i = -1;
	while (table[++i])
		printf("tabla %i: %12s  % 4i\n", i, table[i], org[i]);
	printf("--------------\n");
}