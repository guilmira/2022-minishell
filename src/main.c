/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/10 20:22:42 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//>> a.txt	tiene que crear el fichero.

//esto tiene que funcionar
//ls "akjf<"
//echo '$a'

/** PURPOSE : Store variables in struct that will be kept after loop. */
static void	store_program(t_prog *prog, t_arguments *args)
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
static void	manage_program_heap(t_arguments *arguments, t_prog *prog)
{
	ft_free_split(prog->envp);
	ft_free_split(prog->lenvp);
	free(prog);
	ft_free_split(arguments->envp);
	ft_free_split(arguments->lenvp);
}

/** PURPOSE : Clear memory heap of a single loop */
static void	manage_loop_heap(t_arguments *arguments, t_prog *prog)
{
	store_program(prog, arguments);
	ft_free_split(arguments->envp);
	ft_free_split(arguments->lenvp);
	free_heap_memory(arguments);
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
	g_rv = 1;
	prog = initalize_prog(envp, builtin_str);
	while (true)
	{
		arguments = intialize_arg(prog);
		set_shlvl_num(arguments);
		shell_reader(arguments);
		if (arguments->flag_execution)
			if (!msh_execute(arguments->argv, arguments))
				break ;
		manage_loop_heap(arguments, prog);
	}
	manage_program_heap(arguments, prog);
	ret = arguments->status;
	free_heap_memory(arguments);
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
	set_signal(1);
	//atexit(ft_leaks);
	if (argc != ARG_NUMBER)
		ft_shut(INVALID_ARGC, 0);
	return (shell_loop(envp));
}

//https://datacarpentry.org/shell-genomics/04-redirection/index.html

//<< eof | cat, cat | cat | ls

//echo -nnnnnnnnn -n -nnnnnm

//echo "''$PWD'''qwere"qwqwer$P$P$PWD"'$PWD'"
//echo $TEST > $TEST

//meter un control de top | cat

//ejemplo importantisimo NO BORRAR "ls" "|" "wc" COMMIT LLAMADO "LS EJEMPLO" LO TIENE

//TODO funcion de checckeo por si te meten un Null en la talbla, 
//por memoria o de la manera que sea, cierre minishell en shutdown.

//ESTUDIAR
//en el proceso principal, tras los forks, todos los fd del pipe cerrados
//ejecutarlos en paralelo, no en serie. 
//todos los procesos del fork se lanazarian a la vez