/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:25:59 by asydykna          #+#    #+#             */
/*   Updated: 2022/02/25 13:26:00 by asydykna         ###   ########.fr       */
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
	mnge_heredoc(t_command *command_struct)
{
	char	*delim;
	char	*buf;
	char	*readline_res;

	delim = command_struct->command[1];
	readline_res = NULL;
	buf = ft_strdup("");
	while (delim)
	{
		readline_res = readline("> ");
		if (!readline_res)
			ft_putendl_fd("minishell: warning: here-document delimited by end-of-file (wanted `%s\')\n", 2);// manage %
		if (!ft_strcmp(readline_res, delim))
			break ;
		if (readline_res)
			update_buf(&buf, readline_res);
		free(readline_res);
		readline_res = NULL;
	}
	rl_event_hook = NULL;
	//free(buf);
	free(readline_res);
	ft_putendl_fd(buf, 1);
}
