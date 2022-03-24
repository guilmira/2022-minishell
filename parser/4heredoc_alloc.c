/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4heredoc_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:10:53 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/24 15:41:49 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Heredoc are found in table. */
int	heredoc_found(char **table, int *type, int i)
{
	while (table[++i])
	{
		if (type[i] == 0)
			break ;
		if (!ft_strcmp(HEREDOC, table[i]))
			return (1);
	}
	return (0);
}

/** PURPOSE : Obtain linked list with files (input) of pipe segment. */
t_list	*delimeters_in(char **table, int *type, int i, t_arguments *args)
{
	char	*str;
	t_list	*list_delimeters;

	str = NULL;
	list_delimeters = NULL;
	i = obtain_position(table, i);
	i = i - 1;
	while (table[++i])
	{
		if (type[i] == 0)
			break ;
		if (!ft_strcmp(HEREDOC, table[i]))
		{
			if (type[i + 1] == 2)
			{	
				str = ft_strdup(table[i + 1]);
				if (!str)
					ft_shutdown(str, i, args);
				ft_lstadd_back(&list_delimeters, ft_lstnew(str));
			}
		}
	}
	return (list_delimeters);
}

/** PURPOSE : Check if string only has spaces. */
static int	case_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isspaces(str[i]))
			return (0);
	return (1);
}

/** PURPOSE : Check if there is a lexer symbol with nothing afterwards. */
static int	error_table(char **table)
{
	int	i;

	i = -1;
	while (table[++i])
	{
		if (!ft_strcmp(HEREDOC, table[i]) || !ft_strcmp(PIPE, table[i]) || \
		!ft_strcmp(IN, table[i]) || !ft_strcmp(OUT, table[i]))
			if (!table[i + 1])
				return (1);
		if (!ft_strcmp(HEREDOC, table[i]))
			if (!ft_strcmp(HEREDOC, table[i + 1]) || !ft_strcmp(PIPE, table[i + 1]) || \
			!ft_strcmp(IN, table[i + 1]) || !ft_strcmp(OUT, table[i + 1]))
				return (1);
	}
	return (0);
}

/** PURPOSE : Handles file creation (in case of multipe redirections). */
int	error_detection(char **lexer_table, int *lexer_type, \
t_arguments *args)
{
	if (error_table(lexer_table))
	{
		ft_free_split(lexer_table);
		free(lexer_type);
		printf("Error at lexer. Command line not accepted.\n");
		args->flag_execution = 1;
		return (0);
	}
	if (case_space(lexer_table[0]) || args->flag_file_in == -1 \
	|| args->flag_file_out == -1)
	{
		ft_free_split(lexer_table);
		free(lexer_type);
		if (args->flag_file_in)
			printf("%s: No such file or directory\n", args->file_input);
		if (args->flag_file_in == -1 || args->flag_file_out == -1)
			printf("File or directory not found\n");
		args->flag_execution = 1;
		return (0);
	}
	return (1);
}
