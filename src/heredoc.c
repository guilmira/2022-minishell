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
}

char *
	do_inner_while(char *delim, char **buf, char *readline_res)
{
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
			break ;
		update_buf(buf, readline_res);
		free_pointers(1, readline_res);
	}
	return (*buf);
}

void
	mnge_heredoc(t_list *heredoc_list)
{
	char	*delim;
	char	*buf;
	char	*readline_res;

	readline_res = NULL;
	while (heredoc_list)
	{
		delim = heredoc_list->content;
		buf = ft_strdup("");
		buf = do_inner_while(delim, &buf, readline_res);
		heredoc_list = heredoc_list->next;
	}
	free_pointers(1, buf);
}

int
	heredoc_routine(t_list *heredoc_list)
{
	set_signal(3);
	mnge_heredoc(heredoc_list);
	set_signal(1);
	return (1);
}
