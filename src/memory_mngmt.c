/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mngmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:41:30 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/21 15:02:15 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Store variables in struct that will be kept after loop. */
void
	store_program(t_prog *prog, t_arguments *args)
{
	if (prog->envp)
		ft_free_split(prog->envp);
	prog->envp = copy_array(prog->envp, args->envp, 1);
	if (prog->lenvp)
		ft_free_split(prog->lenvp);
	prog->lenvp = copy_array(prog->lenvp, args->lenvp, 1);
	prog->status = args->status;
	prog->builtin_str = args->builtin_str;
}

/** PURPOSE : Clear memory heap of a single loop */
void
	manage_program_heap(t_arguments *arguments, t_prog *prog)
{
	ft_free_split(prog->envp);
	ft_free_split(prog->lenvp);
	free(prog);
	ft_free_split(arguments->envp);
	ft_free_split(arguments->lenvp);
}

/** PURPOSE : Clear memory heap of a single loop */
void
	manage_loop_heap(t_arguments *arguments, t_prog *prog)
{
	store_program(prog, arguments);
	ft_free_split(arguments->envp);
	ft_free_split(arguments->lenvp);
	
	free_heap_memory(arguments);
}

//PROVISIONAL -- comment if compiling with fsanitize
void
	ft_leaks(void)
{
	system("leaks minishell");
}

void
	set_status_and_shut(t_arguments *args, char *msg)
{
	set_status(args, 1);
	ft_shutdown(msg, 0, args);
}
