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

//an array of function pointers (that takes two arrays of strings and return an int)
static int	(*builtin_func[])(char **, char **) = {
		&msh_echo,
		&msh_cd,
		&msh_pwd,
		&msh_export,
		&msh_unset,
		&msh_env,
		&msh_exit,
		&msh_help
};

int
	msh_num_builtins(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
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
	msh_execute(char **args, char *envp[])
{
	int	i;

	if (args[0] == NULL) //empty command was entered
		return (1);
	i = 0;
	while (i < msh_num_builtins())
	{
		if (strcmp(args[0], g_builtin_str[i]) == 0)
			return ((*builtin_func[i])(args, envp));
		i++;
	}
	return (msh_launch(args));
}
