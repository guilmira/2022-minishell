/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:17:03 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 08:19:31 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

/** PURPOSE : Normi forced. */
static int	advance_and_fix(char *line, int *t, int i, t_list **list)
{
	i = advance_to_next_quote(line, i);
	fix_previous_line(line, *t, i, list);
	*t = i;
	return (i);
}


			//NO BORRAR previo
			/* fix_previous_line(line, t, i, &list);
			t = i + 1;
			str = obtain_symbol(line, i);
			if (line[i + 1] == '<' || line[i + 1] == '>')
			{
				i++;
				t++;
			}
			ft_lstadd_back(&list, ft_lstnew(str));
			i++; */  //y no tenia el t=i

/** PURPOSE : Normi forced. */
static int	arrange_symbols(char *line, int *t, int i, t_list **list)
{
	char	*tmp;
	char	*str;

	tmp = NULL;
	str = NULL;
	fix_previous_line(line, *t, i, list);
	tmp = obtain_symbol(line, i);
	if (line[i + 1] == '<' || line[i + 1] == '>')
		i++;
	str = ft_strjoin(" ", tmp);
	free(tmp);
	ft_lstadd_back(list, ft_lstnew(str));
	i++;
	*t = i;
	return (i);
}

/** PURPOSE : Redo line separating symbols that come without spaces.
 * Uses a linked list to load each fragment 
 * of the new built line with spaces. */
t_list	*build_lexer_list(char *line)
{
	int		i;
	int		t;
	t_list	*list;

	i = 0;
	t = 0;
	list = NULL;
	while (line[i])
	{
		if (is_quote(line[i]))
			i = advance_and_fix(line, &t, i, &list);
		else if (ft_isspaces(line[i]))
			i++;
		else if (line[i] == '=' && line[i + 1] && line[i + 1] != DOUBLE && line[i + 1] != SINGLE)
			i = i + 2;
		else if (is_one_of_lexer_symbols(line[i]))
			i = arrange_symbols(line, &t, i, &list);
		else
			i++;
	}
	fix_previous_line(line, t, i, &list);
	return (list);
}
