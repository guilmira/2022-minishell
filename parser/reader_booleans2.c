/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_booleans2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:41:13 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/04 12:08:17 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Evaluates whether string is < or >. */
static int	is_file_symbol(char *str)
{
	return (is_file_symb(str[0]));
}

/** PURPOSE : Boolean that evaluates if text is part of a command.
 * Such is the case on <echo "text"> or <cat "text">. */
int	is_following_text(char *previous, char *text)
{
	if (is_file_symb(text[0]))
		return (0);
	if (is_special(previous))
		return (1);
	return (0);
}

/** PURPOSE : Evaluates whether string is a command or not. */
static int	is_delimitator(char *str)
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
