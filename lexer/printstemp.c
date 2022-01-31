/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstemp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:49:33 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/06 14:52:07 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printlt(char **lexer_table)
{
	int i;

	i = -1;
	while (lexer_table[++i])
		printf("%i: %s\n", i, lexer_table[i]);
	printf("--------------\n");
}

void printltt(char **table)
{
	int i;

	i = -1;
	while (table[++i])
		printf("tabla %i: %s\n", i, table[i]);
	printf("--------------\n");
}

void printlttt(char **table, int *org)
{
	int i;

	i = -1;
	while (table[++i])
		printf("tabla %i: %12s  % 4i\n", i, table[i], org[i]);
	printf("--------------\n");
}