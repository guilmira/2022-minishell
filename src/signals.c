/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:47:02 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/16 18:05:08 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handler_parent(int s)
{
	if (s == SIGQUIT || s == SIGINT)
	{
		rl_done = 1;
		rl_redisplay();
		ft_putendl_fd("", 2);
		rl_on_new_line();
	}
}

void
	sig_handler(int signum __attribute__((unused)))
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putendl_fd("", 2);
	}
}

void
	handler_heredoc(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGINT)
	{
		g_rv = 0;
		rl_redisplay();
		rl_done = 1;
	}
}

void
	set_signal(int sig_type)
{
	sig_t		handler;

	if (sig_type == 1)
		handler = &handler_parent;
	else if (sig_type == 3)
		handler = &handler_heredoc;
	else
		handler = &sig_handler;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}

void
	eof_exit(t_arguments *args)
{
	ft_putendl_fd("exit", 2);
	ft_free_split(args->envp);
	ft_free_split(args->lenvp);
	free_heap_memory(args);
	exit(EXIT_SUCCESS);
}
