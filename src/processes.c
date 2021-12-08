/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:47:01 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/08 13:00:00 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//an array of function pointers (that takes two arrays of strings and return an int)
static int	(*builtin_func[])(char **, t_data *) = {
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
	msh_launch(char **argu)
{

	t_arguments	*args;
	args = NULL;

	int argc;
	argc = 4; //pipex ls wc cat
	char **envp;
	char string[] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands";
	
	//no va a coger con las omillas por la manera en la que lee. solo cogera comandos limpios
	envp = ft_calloc(1, sizeof(char *));
	envp[0] = string;
	args = arg_reader(argc, argu, envp);
	args->fds = arg_descriptors(args);
	process_exe(args);
	return (1);
}

int
	msh_execute(char **args, t_data *data)
{
	int	i;

	if (args[0] == NULL) //empty command was entered
		return (1);
	i = 0;
	while (i < msh_num_builtins())
	{
		if (strcmp(args[0], g_builtin_str[i]) == 0)
			return ((*builtin_func[i])(args, data));
		i++;
	}
	return (msh_launch(args));
}
