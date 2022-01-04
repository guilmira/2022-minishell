/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_booleans.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:33:05 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/04 11:39:17 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Evaluates whether char is a sufix. */
int	is_sufix(char z)
{
	return (z == '-');
}

/** PURPOSE : Evaluates whether char is a pipe. */
int	is_pipe(char z)
{
	return (z == '|');
}

/** PURPOSE : Evaluates whether char is a pipe. */
int	is_file_symb(char z)
{
	return (z == '<' || z == '>');
}

int	is_file_symbol(char *str)
{
	return(is_file_symb(str[0]));
}

/** PURPOSE : Evaluates whether string is a command or not. */
int	is_delimitator(char *str)
{
	if (!str)
		return (0);
	return (is_sufix(str[0]) || is_pipe(str[0]));
}

/** PURPOSE : Auxiliar function to evaluate if its command. */
static int	check_previous_place(char *previous)
{
	if (is_delimitator(previous))
		return (1);
	if (previous[0] == '<')
		return (1);
	if (is_special(previous) || is_file_symbol(previous))
		return (0);
	return (1);
}

/** PURPOSE : Evaluate whether string imput is command or not. */
int	is_command(char **argv, char *command, int position)
{
	if (!command)
		return (0);
	if (is_file_symbol(command))
		return (0);
	if (is_delimitator(command))
		return (0);
	if (position == 0)
	{
		if (argv[position + 1])
		{
			if (argv[position + 1][0] == '<')
				return (0);
			else
				return (1);
		}
		else
			return(1); //estaria bien comprobar si abre fichero etc.
	}
	if (!check_previous_place(argv[position - 1]))
		return (0);
	return (1);
}

/** PURPOSE : Count total number of commands. */
int	count_commands(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (argv[++i])
		if (is_command(argv, argv[i], i))
			j++;
	return (j);
}