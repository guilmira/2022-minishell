/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:17:03 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/07 18:13:25 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Check for symbols. */
static int	is_one_of_lexer_symbols(char symbol)
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

/* USED IN LEXER QUOTES AND IN DOLLAR EXPANSION. */
void	fix_previous_line(char *line, int t, int i, t_list **list)
{
	int		lenght;
	char	*str;

	str = NULL;
	if (i - 1 < 0)
		return ;
	lenght = i - t;
	str = ft_substr(line, t, lenght);
	if (!str)
		return ;
	ft_lstadd_back(list, ft_lstnew(str));
}

/** PURPOSE : Return string of symbol to load in linkedL. */
static char	*obtain_symbol(char *line, int i)
{
	char	*str;

	if (line[i + 1] == '<' || line[i + 1] == '>')
	{
		str = ft_substr(line, i, 3);
		if (!str)
			return (NULL);
		str[2] = ' ';
	}
	else
	{
		str = ft_substr(line, i, 2);
		if (!str)
			return (NULL);
		str[1] = ' ';
	}
	return (str);
}

/** PURPOSE : Redo line separating symbols that come without spaces.
 * Uses a linked list to load each fragment 
 * of the new built line with spaces. */
t_list	*build_lexer_list(char *line)
{
	int		i;
	int		t;
	char	*str;
	t_list	*list;

	list = NULL;
	i = 0;
	t = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			i = advance_to_next_quote(line, i);
			fix_previous_line(line, t, i, &list);
			t = i;
		}
		else if (ft_isspaces(line[i]))
			i++;
		else if (line[i] == '=' && line[i + 1])
			i = i + 2;
		else if (is_one_of_lexer_symbols(line[i]))
		{
			fix_previous_line(line, t, i, &list);
			t = i + 1;
			str = obtain_symbol(line, i);
			if (line[i + 1] == '<' || line[i + 1] == '>')
			{
				i++;
				t++;
			}
			ft_lstadd_back(&list, ft_lstnew(str));
			i++;
		}
		else
			i++;
	}
	fix_previous_line(line, t, i, &list);
	return (list);
}
