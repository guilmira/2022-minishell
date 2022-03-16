/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:25:59 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/14 10:14:27 by guilmira         ###   ########.fr       */
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

char *
	do_inner_while(char *delim, char **buf)
{
	char	*readline_res;

	while (delim && g_rv)
	{
		readline_res = readline(HEREDOC_PROMPT);
		if (!readline_res)
		{
			printf("minishell: warning: here-document "
				   "delimited by end-of-file (wanted `%s')\n", delim);
			break ;
		}
		if (!ft_strcmp(delim, readline_res))
		{
			free(readline_res);
			break ;
		}
		update_buf(buf, readline_res);
	}
	return (*buf);
}

void
	mnge_heredoc(t_list *heredoc_list, t_arguments *args)
{
	char	*delim;
	char	*buf;
	t_list	*temp;

	temp = heredoc_list;
	buf = ft_strdup("");
	while (heredoc_list && heredoc_list->content)
	{
		delim = heredoc_list->content;
		buf = do_inner_while(delim, &buf);
		heredoc_list = heredoc_list->next;
	}
	args->heredoc_list = temp;
	args->here_redir = buf;
}

int
	heredoc_routine(t_list *heredoc_list, t_arguments *args)
{
	set_signal(3);
	mnge_heredoc(heredoc_list, args);
	set_signal(1);
	return (1);
}
