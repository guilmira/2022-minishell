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

char *
	get_env_var(char **envp, char *needle)
{
	char	*var;
	int		i;
	int		len;

	var = NULL;
	var = ft_concat(needle, "=");
	len = (int )ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_memcmp(envp[i], var, len))
		{
			free(var);
			var = ft_strdup(envp[i] + len);
			return (var);
		}
		i++;
	}
	free(var);
	return (NULL);
}

void
	set_new_var(char *var, t_arguments *arg)
{
	char	*temp_args[3];

	temp_args[0] = "nothing";
	temp_args[1] = var;
	temp_args[2] = NULL;
	export_new_variables(temp_args, arg);
}

void
	renew_pwds(t_arguments *arg, char *old_path)
{
	char	*cur_path;

	delete_env_var(arg, 7, "OLDPWD=");
	set_new_var(old_path, arg);
	cur_path = ft_strjoin("PWD=", getcwd(NULL, 0));
	delete_env_var(arg, 4, "PWD=");
	set_new_var(cur_path, arg);
}

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
