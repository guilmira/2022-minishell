/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:40:28 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/03 13:40:40 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** __attribute__((unused))
** Command for disabling unused variable warnings
*/

int
	msh_echo(char **args __attribute__((unused)), t_data *data __attribute__((unused)))
{
	return (0);
}

int
	msh_cd(char **args, t_data *data __attribute__((unused)))
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
	msh_pwd(char **args __attribute__((unused)), t_data *data __attribute__((unused)))
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror("pwd() error");
	printf("%s\n\n", path);
	return (1);
}

int
	msh_help(char **args __attribute__((unused)), t_data *data __attribute__((unused)))
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
	return (1);
}
