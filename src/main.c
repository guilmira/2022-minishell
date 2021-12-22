/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/22 04:53:34 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_arguments
	*init_arg(char *envp[], char **builtin_str)
{
	t_arguments	*arguments;

	arguments = ft_calloc(1, sizeof(t_arguments));
	if (!arguments)
		ft_shut(MEM, 0);
	arguments->envp = envp;
	init_builtins(builtin_str);
	arguments->builtin_str = builtin_str; //builtin_str has being declared on stack instead of at heap.
	// ^  couldn´t this bring problems??
	init_builtin_func_arr(arguments->builtin_func);
	return (arguments);
}

/** PURPOSE : Main loop of the shell.
 * 1. Reads the command from standard input and load it.
 * 2. Execute main routine. Forks cmmands into processes and execute them. */
int
	shell_loop(char *envp[])
{
	int			status;
	t_arguments	*arguments;
	char		*builtin_str[9];
	
	arguments = NULL;
	arguments = init_arg(envp, builtin_str);
	while (true)
	{
		shell_reader(envp, arguments);
		if (arguments->flag_execution)
			status = msh_execute(arguments->argv, arguments);
		arguments->flag_execution = 0;
		free_heap_memory(arguments);
		if (!status)
			break ;
	}
	return (arguments->status);
}

//PROVISIONAL -- comment if compiling with fsanitize
void	*ft_leaks(void)
{
	system("leaks minishell");
	return (NULL);
}

/** EXECUTION : ./minishell
 * This program will run a student made version of the bash console.
 * 		msh> [INSERT COMMANDS]											*/
int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	//atexit(ft_leaks());
	if (argc != ARG_NUMBER)
		ft_shut(INVALID_ARGC, 0);
	// 1. Load config files, if any.
	return (shell_loop(envp));
	// 3. Perform shutdown/cleanup
	//return (EXIT_SUCCESS);
}

//cat | cat | ls
	//wait(status); Si esta fuera hara todo simutaneo. es como funciona bash
	//si estuvies ddentro, es cuando en cada proceso espera.