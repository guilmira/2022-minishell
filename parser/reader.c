/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:35:59 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/24 11:02:47 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Reads command line and allocates it into string.
 * If pointer line exists and is not empty, adds it to history. */
static char	*read_shell_line(void)
{
	char	*line;

	line = readline(MSHELL);
	if (!line)
		return (NULL);
	if (line[0])
		add_history(line);
	return (line);
}

/** PURPOSE : Obtain COMMAND line and apply an initial filter. */
char	*read_and_filter_line(t_arguments *args)
{
	char	*line;

	line = read_shell_line();
	if (!line)
		return (NULL);
	//args->status = 1;// I guess this line should be higher, so status is put before exit
	if (pre_filter(line))
	{
		free(line);
		return (EMPTY_LINE);
	}
	args->flag_execution = 1;
	return (line);
}

static int case_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isspaces(str[i]))
			return (0);
	return (1);
}



/* typedef struct s_file_list
{
	char				*string;
	int					append;
	struct s_file_list	*next;
}						t_file_list;
 */

void	prepare_file(char *content, t_list **list_input, t_arguments *args)
{	
	char	*str;
	
	str = NULL;
	str = ft_strdup(content);
	if (!str)
		ft_shutdown(MEM, 0, args);
	ft_lstadd_back(list_input, ft_lstnew(str));
	
}

void assign_type(char *content, t_list **list_type, t_arguments *args)
{
	int		*ptr;

	ptr = NULL;
	ptr = ft_calloc(1, sizeof(int));
	if (!ptr)
		ft_shutdown(MEM, 0, args);
	*ptr = -1;
	if (!ft_strcmp(content, OUT))
		*ptr = 1;
	else if (!ft_strcmp(content, IN))
		*ptr = 2;
	else if (!ft_strcmp(content, APPEND))
		*ptr = 3;
	else if (!ft_strcmp(content, HEREDOC))
		*ptr = 4;
	ft_lstadd_back(list_type, ft_lstnew(ptr));
}

void	management_file(char **table, t_arguments *args)
{
	int		i;
	t_list	*list_input;
	t_list	*list_type;

	list_input = NULL;
	list_type = NULL;
	i = -1;
	while (table[++i])
	{
		if (!ft_strcmp(table[i], OUT) || !ft_strcmp(table[i], APPEND) || !ft_strcmp(table[i], IN) || !ft_strcmp(table[i], HEREDOC))
		{
			prepare_file(table[i + 1], &list_input, args);
			assign_type(table[i],  &list_type, args);
		}
	}
	
	int  *ptr;
	while (list_input)
	{
		ptr = list_type->content;
		printf("lista: %s\n", list_input->content);
		printf("tipo: %i\n", *ptr);
		list_input = list_input->next;
		list_type = list_type->next;
	}
}

/** PURPOSE : Reads command line. Loads arguments into structure. 
 * 1. Reads command line and applies a pre-filter.
 * 2. Parses and rearranges arguments. i.e: "ls -la" will be a single arg.
 * 3. Counts number of total commands. i.e: "ls -la" "wc -l" = 2 total args.
 * 4. Creates linked list to manage any number of commands. */
void	shell_reader(char *envp[], t_arguments	*args)
{
	char		*line;
	char		**table;
	char		**lexer_table;
	int			*lexer_type;

	line = read_and_filter_line(args);
	if (!line)
		eof_exit(args);
	if (!line[0])
		return ;
	lexer_table = main_lexer(line, args);
	free(line);
	if (!lexer_table)
		return ;
	lexer_type = class_lex_table(lexer_table);
	if (!lexer_type)
		ft_shutdown(MEM, errno, args);
	table = NULL;
	printer(lexer_table, lexer_type);
	table = get_command_table(lexer_table, args, lexer_type);
	management_file(lexer_table, args);
	ft_free_split(lexer_table);
	free(lexer_type);
	if (case_space(table[0]))
	{
		ft_free_split(table);
		args->flag_execution = 1;
		return ;
	}
	arg_reader(count_table(args->argv), table, envp, args);
	ft_free_split(table);
}
