/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:25:59 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/13 11:16:53 by guilmira         ###   ########.fr       */
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

void
	mnge_heredoc(t_list *heredoc_list)
{
	char	*delim;
	char	*buf;
	char	*readline_res;

	delim = heredoc_list->content; //access to first element of the list
	//printf("delimeter is: %s\n", delim);
	readline_res = NULL;
	buf = ft_strdup("");
	while (delim && g_rv)
	{
		readline_res = readline(HEREDOC_PROMPT);
		if (!readline_res)
		{
			ft_putendl_fd("minishell: warning: here-document delimited by end-of-file (wanted `%s\')\n", 2);// manage %
			break ;
		}
		if (!ft_strcmp(delim, readline_res))
			break ;
		update_buf(&buf, readline_res);
		free_pointers(1, readline_res);
	}
}

int
	heredoc_routine(t_list *heredoc_list)
{
	set_signal(3);
	mnge_heredoc(heredoc_list);
	set_signal(1);
	return (1);
}
