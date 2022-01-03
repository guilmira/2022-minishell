/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/16 10:23:42 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes fork function for a single command. */
void	single_process(t_arguments *args)
{
	int	status;
	int	identifier;
	
	identifier = fork();
	if (identifier == 0)
		single_son(args);
	else if (identifier > 0)
		wait(&status);
	else
		ft_shutdown(FORK_ERROR, 0, args);
}
