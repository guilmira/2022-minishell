/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter_advanced.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:15:17 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/17 11:31:37 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Boolean, checks if first char is just a symbol. */
static int	only_symbol(char *line)
{
	char	z;

	z = line[0];
	return (z == '|' || z == '-');
}

/** PURPOSE : Check for lexer symbols. */
int	is_one_of_lexer_symbols(char symbol)
{
	int		i;
	char	*option[TOTAL_SYMBOLS + 1];
	char	*option_name[TOTAL_SYMBOLS + 1];

	if (!symbol)
		return (0);
	init_options(option, option_name);
	i = -1;
	while (option[++i])
		if (symbol == option[i][0])
			return (1);
	return (0);
}

static int	evaluate_inside_quotes(char *line, int i, int *flag)
{
	int	j;
	
	j = i;
	i = advance_to_next_quote(line, i);
	i = i - 1;
	while (line[++j] && j < i)
		if (!ft_isspaces(line[j]))
			*flag = 3;
	return (i);
}

/** PURPOSE : Prevent unclosed symbols like ls | 
 * or
 * ls < , ls << and so on. */
int	unclosed_filter(char *line)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		if (is_quote(line[i]))
			i = evaluate_inside_quotes(line, i, &flag);
		else if (is_one_of_lexer_symbols(line[i]))
			flag++;
		else if (ft_isalnum(line[i]))
			flag = 0;
		if (flag == 3)
		{
			flag = 0;
			break ;
		}
	}
	if (flag)
		return (1);
	return (0);
}

/** PURPOSE : SECOND filter of command line.
 * Related to proper use of quotes. */
int	pre_filter_advanced(char *line)
{
	if (only_symbol(line))
	{
		printf("parse error on initial symbol\n");
		return (1);
	}
	if (quotes_filter(line))
	{
		printf("Quotes (\" or '') must be closed\n");
		return (1);
	}
	if (unclosed_filter(line))
	{
		printf("Lexer symbols must be followed by sensible content\n");
		return (1);
	}
	return (0);
}
