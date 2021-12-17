/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:00:55 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/17 11:00:56 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	get_paths(char **args, t_arguments *arg, char **path, char **old_path)
{
	(*path) = NULL;
	(*old_path) = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!args[1] || !ft_memcmp(args[1], "~", 2) || !ft_memcmp(args[1], "--", 3))
		(*path) = get_env_var(arg->envp, "HOME");
	else if (!ft_memcmp(args[1], "-", 2))
		(*path) = get_env_var(arg->envp, "OLDPWD");
	else
		(*path) = args[1];
}

int
	msh_cd(char **args, t_arguments *arg)
{
	char	*path;
	char	*old_path;
	int		fd;

	fd = get_fd(arg->file_output);
	if (get_arr_len(args) > 2)
	{
		ft_putstr_fd("msh: cd: too many arguments\n", fd);
		return (1);
	}
	get_paths(args, arg, &path, &old_path);
	if (chdir(path) != 0)
	{
		perror("msh");
		arg->status = 127;
	}
	else
		renew_pwds(arg, old_path);
	free(path);
	free(old_path);
	set_status(arg, 0);
	return (1);
}

