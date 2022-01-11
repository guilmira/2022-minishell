/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2022/01/05 08:46:52 by asydykna         ###   ########.fr       */
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
	t_prog		*prog; //Explanation: new struct. No panic, its only function is to carry a pointer to the variables that are mantained outsidde the loop.
	t_arguments	*arguments;
	char		*builtin_str[9]; //DUDA: cuanta memoria reserva para cada uno de los strings? Declaracion en el stack solo te reserv aespacio para punteros.

	prog = NULL;
	arguments = NULL;
	prog = initalize_prog(envp, builtin_str); //Explanation: now we only init outside the loop the struct that will not be freed.
	while (true)
	{
		arguments = intialize_arg(prog); //Explanation: arguments struct has changed as it had to be INSIDE of the loops.
		shell_reader(envp, arguments);
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


//tdo, ls + name of file/directory

//to do configurar exclamacion.
/* minishell$ echo $?
127
minishell$ ! ls | dsgs
dsgs: orden no encontrada
minishell$ echo $?
0 */

//https://datacarpentry.org/shell-genomics/04-redirection/index.html
 //cat | cat | ls
	//wait(status); Si esta fuera hara todo simutaneo. es como funciona bash
	//si estuvies ddentro, es cuando en cada proceso espera.
