/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/04 12:09:38 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes fork function for a single command. */
int
	single_process(t_arguments *args)
{
	int	status;
	int	identifier;

	//g_rv = 1;
	identifier = fork();
	if (identifier == 0)
	{
		g_rv = single_son(args);
		printf("g_rv = %d\n", g_rv);
		exit (0);
	}
	else if (identifier > 0)
	{
		wait(&status);
		//exit(0); //killing father to avoid duplication
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	printf("before exit g_rv = %d\n", g_rv);
	return (g_rv); //to make function work
}
