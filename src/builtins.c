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

/*
** SYNOPSIS: our version of pwd command.
*/
int
	msh_pwd(char **args __attribute__((unused)),
			t_arguments *arg)
{
	char	*path;
	int		fd;

	fd = get_fd(arg->file_output);
	path = getcwd(NULL, 0);
	if (!path)
		perror("pwd() error");
	set_status(arg, 0);
	return (1);
}

/*
** SYNOPSIS: our version of env command.
*/
int
	msh_env(char **args __attribute__((unused)), t_arguments *arg)
{
	int		fd;

	fd = get_fd(arg->file_output);
	print_str_arr(arg->envp, fd);
	ft_putendl_fd("", fd);
	set_status(arg, 0);
	return (1);
}

/*
** SYNOPSIS: builtin help command.
*/
int
	msh_help(char **args __attribute__((unused)),
			 t_arguments *arg)
{
	int	i;
	int	fd;

	fd = get_fd(arg->file_output);
	i = 0;
	ft_putendl_fd("\nminishell", fd);
	ft_putendl_fd("Copyright (c) Ardak Sydyknazar "
		"and Guillermo Mira Osuna, 2022.\n", fd);
	ft_putendl_fd("Type program names and arguments, and hit enter.", fd);
	ft_putendl_fd("The following are built in:", fd);
	while (i < msh_num_builtins(arg))
	{
		ft_putstr_fd("\t", fd);
		ft_putendl_fd(arg->builtin_str[i], fd);
		i++;
	}
	ft_putendl_fd("Use the man command for information on other programs.", fd);
	set_status(arg, 0);
	return (1);
}
