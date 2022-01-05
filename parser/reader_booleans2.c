/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_booleans2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:41:13 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/05 17:51:54 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Boolean that evaluates if text is part of a command.
 * Such is the case on <echo "text"> or <cat "text">. */
int	is_following_text(char *previous, char *text)
{
	if (is_file_symbol(text[0]))
		return (0);
	if (is_special(previous))
		return (1);
	return (0);
}

/** PURPOSE : Auxiliar function to evaluate if its command. */
static int	check_previous_place(char *previous)
{
	int	i;
	char	*option[TOTAL_SYMBOLS];
	char	*option_name[TOTAL_SYMBOLS];
	
	init_options(option, option_name);
	if (ft_strcmp(previous, option_name[0]) == 0) //el pipe
		return (1);
	i = 1;
	while (++i < 6)
		if (ft_strcmp(previous, option_name[i]) == 0) //los <<, <, >>, >
			return (0);
	if (is_sufix(previous[0])) //si es sufijo inmediatamente no es
		return (0);
	if (is_special(previous)) //si es especial inmeiatmaente no es
		return (0);
	return (1);
}

int	token_is_lexic(char *token)
{
	if (ft_strncmp(token, "lex_", 4) == 0)
		return (1);
	else
		return (0);	
}

/** PURPOSE : Evaluate whether string input is command or not.
 * Assumption: the string table given has gone through lexical analyser. */
int	is_command(char **lexer_table, char *command, int position)
{
	if (!command)
		return (0);
	if (token_is_lexic(command))
		return (0);
	if (is_sufix(command[0]))
		return (0);
	if (position == 0)
		return (1); //estaria bien comprobar si abre fichero etc.
	if (!check_previous_place(lexer_table[position - 1]))
		return (0);
	return (1);
}
