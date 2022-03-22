/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:25:59 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/17 13:04:40 by guilmira         ###   ########.fr       */
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
	mnge_heredoc(char *delim, t_arguments *args, int i, char *buf)
{
	int		j;
	t_list	*temp;

	buf = do_inner_while(delim, &buf);
	temp = args->here_output;
	j = 0;
	while (j < i)
	{
		args->here_output = args->here_output->next;
		j++;
	}
	args->here_output->content = buf;
	args->here_output = temp;
}

int
	heredoc_routine(t_list *heredoc_list, t_arguments *args)
{
	int		i;
	int		j;
	t_list	*temp;
	char	*buf;

	i = 0;
	j = ft_lstsize(args->heredoc_list);
	temp = heredoc_list;
	while (i < j && temp->content)
	{
		set_signal(3);
		buf = ft_strdup("");
		mnge_heredoc(temp->content, args, i, buf);
		set_signal(1);
		temp = temp->next;
		i++;
	}
	return (1);
}
