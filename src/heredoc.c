/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:25:59 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/25 00:20:49 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	update_buf(char **buf, char *readline_res)
{
	char	*res;
	char	*tmp;

	tmp = *buf;
	res = ft_strjoin(readline_res, "\n");
	*buf = ft_strjoin(*buf, res);
	free(tmp);
	free(res);
	free(readline_res);
}

int
	event(void)
{
	return (1);
}

char *
	do_inner_while(char *delim, char **buf)
{
	char	*readline_res;

	rl_event_hook = event;
	set_signal(3);
	while (delim && g_rv)
	{
		readline_res = readline(HEREDOC_PROMPT);
		if (!readline_res)
		{
			printf("minishell: warning: here-document "
				"delimited by end-of-file (wanted `%s')\n", delim);
			break ;
		}
		if (!ft_strcmp(delim, readline_res)
			&& (ft_strlen(delim) == ft_strlen(readline_res)))
		{
			free(readline_res);
			break ;
		}
		update_buf(buf, readline_res);
	}
	return (*buf);
}

void
	mnge_heredoc(char *delim, t_arguments *args, \
	char *buf, t_command *command_struct)
{
	if (command_struct->heredoc_result)
		free(command_struct->heredoc_result);
	buf = do_inner_while(delim, &buf);
	command_struct->heredoc_result = buf;
	if (!g_rv)
	{
		set_status(args, 130);
		free(command_struct->heredoc_result);
		command_struct->heredoc_result = NULL;
		command_struct->print_heredoc = false;
	}
}

int
	heredoc_routine(t_command *command_struct, t_arguments *args)
{
	int		i;
	int		j;
	t_list	*temp;
	char	*buf;

	i = 0;
	buf = NULL;
	j = ft_lstsize(command_struct->list_delimeters);
	temp = command_struct->list_delimeters;
	while (i < j && temp->content)
	{
		set_signal(3);
		buf = ft_strdup("");
		mnge_heredoc(temp->content, args, buf, command_struct);
		set_signal(1);
		temp = temp->next;
		i++;
	}
	return (1);
}
