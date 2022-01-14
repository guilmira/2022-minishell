/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2022/01/13 12:43:56 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Store variables in struct that will be kept after loop. */
static void	store_program(t_prog *prog, t_arguments *args)
{
	prog->envp = args->envp;
	prog->status = args->status;
	prog->builtin_str = args->builtin_str;
}

/** PURPOSE : Main loop of the shell.
 * 1. Reads the command from standard input and load it.
 * 2. Execute main routine. Forks commands into processes and execute them. */
int
	shell_loop(char *envp[])
{
	//int			status; commented because otherwise it says unused
	t_prog		*prog;
	t_arguments	*arguments;
	char		*builtin_str[9];

	prog = NULL;
	arguments = NULL;
	prog = initalize_prog(envp, builtin_str);
	while (true)
	{
		arguments = intialize_arg(prog);
		set_shlvl_num(arguments);
		shell_reader(envp, arguments); //la joya de la corona
		if (arguments->flag_execution)
			//prog->status = msh_execute(arguments->argv, arguments); //TODO :falta introducir set_status(t_arguments *arg, int status) en los pipes.ls
			if (!msh_execute(arguments->argv, arguments)) //We can't rely on prog->status to exit.
				break ;
		store_program(prog, arguments);

		//FOUND OUT SEGFAULT WITH SPLIT. THE PROBLEM IS THAT ARGV IS MODIFIED WHEN USED 'CD'AND NOT TERMINATED IN NULL.
		if (arguments->flag_execution)
			if (!ft_strcmp(arguments->argv[0], "cd")) 
				arguments->argv[1] = NULL;
		//TEMPORARY ^


		free_heap_memory(arguments); //free_heap now frees arguments as well. BUT keeps prog.
		if (0) //temporal
			break ;
		/* if (prog->status)
			break ; */
	}
	free(prog);
	return (arguments->status);
}

//TODO read variables like a=500

//PROVISIONAL -- comment if compiling with fsanitize
/* void	*ft_leaks(void)
{
	system("leaks minishell");
	return (NULL);
} */

/** EXECUTION : ./minishell
 * This program will run a student made version of the bash console.
 * 		msh> [INSERT COMMANDS]											*/
int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);

	//atexit(ft_leaks()); //on exit, gves seg fault.
	 if (argc != ARG_NUMBER)
		ft_shut(INVALID_ARGC, 0);
	return (shell_loop(envp));
}


//TODO review protection of mallocs etc on all parts of the code. 

//tdo, ls + name of file/directory

//to do configurar exclamacion.
/* minishell$ echo $?
127
minishell$ ! ls | dsgs
dsgs: orden no encontrada
minishell$ echo $?
0 */

//https://datacarpentry.org/shell-genomics/04-redirection/index.html


//TODO: review whats happening with printenv.