/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2022/02/22 14:54:54 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

/** PURPOSE : Store variables in struct that will be kept after loop. */
static void	store_program(t_prog *prog, t_arguments *args)
{
	if (prog->envp)
		ft_free_split(prog->envp);
	prog->envp = copy_array(prog->envp, args->envp, 1);
	prog->status = args->status;
	prog->builtin_str = args->builtin_str;
}

/** PURPOSE : Main loop of the shell.
 * 1. Reads the command from standard input and load it.
 * 2. Execute main routine. Forks commands into processes and execute them. */
int
	shell_loop(char *envp[])
{
	t_prog		*prog;
	t_arguments	*arguments;
	char		*builtin_str[9];
	int			ret;

	prog = NULL;
	arguments = NULL;
	prog = initalize_prog(envp, builtin_str);
	while (true)
	{
		arguments = intialize_arg(prog);
		set_shlvl_num(arguments);
		shell_reader(envp, arguments);
		if (arguments->flag_execution)
			if (!msh_execute(arguments->argv, arguments))
				break ;
		store_program(prog, arguments);
		ft_free_split(arguments->envp);
		free_heap_memory(arguments);
		//system("leaks minishell");
	}
	ft_free_split(prog->envp);
	free(prog);
	ft_free_split(arguments->envp);
	ret = arguments->status;
	free_pointers(1, arguments);
	return (ret);
}

//PROVISIONAL -- comment if compiling with fsanitize
void	ft_leaks(void)
{
	system("leaks minishell");
}

/** EXECUTION : ./minishell
 * This program will run a student made version of the bash console.
 * 		msh> [INSERT COMMANDS]											*/
int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	//atexit(ft_leaks);
	if (argc != ARG_NUMBER)
		ft_shut(INVALID_ARGC, 0);
	return (shell_loop(envp));
}

//https://datacarpentry.org/shell-genomics/04-redirection/index.html

//TODO ctrl + c complexity when several levels of ms. it has to close. it can work with PID
