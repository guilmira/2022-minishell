/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/22 06:31:14 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Main loop of the shell.
 * 1. Reads the command from standard input and load it.
 * 2. Execute main routine. Forks cmmands into processes and execute them. */
int
	shell_loop(char *envp[])
{
	int			status;
	t_prog		*prog;
	t_arguments	*arguments;
	char		*builtin_str[9];
	
	prog = NULL;
	arguments = NULL;
	prog = initalize_prog(envp, builtin_str); //Explanation: now we only init outside the loop the struct that is not freed.
	while (true)
	{
		arguments = intialize_arg(prog); 
		//Explanation: arguments has changed as it had to be inside of the loops.
		//Otherwise, seg faults after serveral iterations were unavoidable.
		shell_reader(envp, arguments);
		if (arguments->flag_execution)
			status = msh_execute(arguments->argv, arguments);
		arguments->flag_execution = 0;
		free_heap_memory(arguments); //free_heap now frees arguments as well. BUT keeps prog.
		if (!status)
			break ;
	}
	status = prog->status;
	free(prog);
	return (status);
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


//one of the errors right now
//ls // export // then only a pipe --> seg fault
//or ls the only a pipe. the reason is, because arguments should be freed.