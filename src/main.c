/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/18 11:16:12 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* char
	**split_line(char *line)
{
	int		bufsize;
	int		position;
	char	**tokens;
	char	*token;

	init_builtins();
	bufsize = TOK_BUFSIZE;
	position = 0;
	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "msh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "msh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL; //What if position == bufsize?
	return (tokens);
} */

/** PURPOSE : Main loop of the shell. 
 * 1. Reads the command from standard input and load it.
 * 2. Execute main routine. Forks cmmands into processes and execute them. */
int
	shell_loop(char *envp[])
{
	int			status;
	char		**temp_envp;
	t_arguments	*arguments;
	int			temp_status;
	char		*builtin_str[9];

	temp_envp = NULL;
	temp_status = 0;
	init_builtins(builtin_str);
	while (true)
	{

		arguments = shell_reader(envp, builtin_str);
		arguments->status = temp_status;
		if (temp_envp != NULL && arguments)
			arguments->envp = temp_envp;
		if (arguments)
		{
			status = msh_execute(arguments->argv, arguments);
			temp_envp = arguments->envp;
			temp_status = arguments->status;
		}
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