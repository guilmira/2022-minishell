/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_auxiliar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:46:01 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/09 14:54:07 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/** PURPOSE : Evaluates whether char is a sufix. */
static int is_sufix(char z)
{
	return (z == '-');
}

/** PURPOSE : Evaluates whether char is a pipe. */
static int is_pipe(char z)
{
	return (z == '|');
}

/** PURPOSE : Evaluates whether string is a command or not. */
int	is_command(char *str)
{
	if (!str)
		return (0);
	return (!is_sufix(str[0]) && !is_pipe(str[0]));
}

/** PURPOSE : Count total number of commands. */
int	count_commands(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		if (is_command(argv[i]))
			i++;	
	return (i);
}