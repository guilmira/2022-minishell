/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:47:01 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/01 13:47:02 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//an array of builtin command names
char *builtin_str[] = {
		"cd",
		"help",
		"exit"
};

//an array of function pointers (that take array of strings and return an int)
int (*builtin_func[]) (char **) = {
		&msh_cd,
		&msh_help,
		&msh_exit
};


int
	msh_num_builtins(void)
{
	return (sizeof(builtin_str) / sizeof(char *));
}

int
	msh_cd(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "msh: expected argument to \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("msh");
	}
	return (1);
}

int
	msh_help(char **args __attribute__((unused)))
{
	int	i;

	i = 0;
	printf("minishell\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	while (i < msh_num_builtins())
	{
		printf("  %s\n", builtin_str[i]);
		i++;
	}
	printf("Use the man command for information on other programs.\n");
	return (1);
}

/*
** __attribute__((unused))
** Command for disabling unused variable warnings
*/
int
	msh_exit(char **args __attribute__((unused)))
{
	return (0);
}

int
	msh_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0) //child process
	{
		if (execvp(args[0], args) == -1)
		{
			perror("msh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) //FORK ERROR
	{
		perror("msh");
	}
	else //parent process
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
	return (1);
}

int
	msh_execute(char **args)
{
	int	i;

	if (args[0] == NULL) //empty command was entered
		return (1);
	i = 0;
	while (i < msh_num_builtins())
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return ((*builtin_func[i])(args));
		i++;
	}
	return (msh_launch(args));
}