/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:40:28 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 11:15:32 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** __attribute__((unused))
** Command for disabling unused variable warnings
*/

//TODO: there is a segfault if we send nothing to the program,
// (just press enter) or it is just a symbol;

int
	msh_pwd(char **args __attribute__((unused)),
			t_arguments *arg)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror("pwd() error");
	printf("%s\n", path);
	set_status(arg, 0);
	return (1);
}

int
	msh_help(char **args __attribute__((unused)),
			 t_arguments *arg)
{
	int	i;

	i = 0;
	printf("minishell\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	while (i < msh_num_builtins())
	{
		printf("  %s\n", g_builtin_str[i]);
		i++;
	}
	printf("Use the man command for information on other programs.\n");
	set_status(arg, 0);
	return (1);
}
