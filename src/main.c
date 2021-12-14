/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 12:04:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	init_builtins(void)
{
	g_builtin_str[0] = "echo";
	g_builtin_str[1] = "cd";
	g_builtin_str[2] = "pwd";
	g_builtin_str[3] = "export";
	g_builtin_str[4] = "unset";
	g_builtin_str[5] = "env";
	g_builtin_str[6] = "exit";
	g_builtin_str[7] = "help";
}

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
void	shell_loop(char *envp[])
{
	int			status;
	t_arguments	*arguments;
	char **temp_envp;
	temp_envp = NULL;

	init_builtins();
	while (true)
	{
		printf("msh> ");
		fflush(0); //provisional
		arguments = shell_reader(envp);
		if (temp_envp != NULL)
			arguments->envp = temp_envp;
		if (arguments)
			status = msh_execute(arguments->argv, arguments);
		temp_envp = arguments->envp;
		//free_heap_memory(arguments);
		if (!status)
			break ;
	}
}

/** EXECUTION : ./minishell
 * This program will run a student made version of the bash console.
 * 		msh> [INSERT COMMANDS]											*/
int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	if (argc != ARG_NUMBER)
		ft_shut(INVALID_ARGC, 0);
	// 1. Load config files, if any.
	shell_loop(envp);
	// 3. Perform shutdown/cleanup
	return (EXIT_SUCCESS);
}
