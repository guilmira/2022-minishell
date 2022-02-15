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

/*
** SYNOPSIS: returns value for env variable passed as second argument.
** If variable is not found returns NULL
*/
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
			free_pointers(1, var);
			var = ft_strdup(envp[i] + len);
			return (var);
		}
		i++;
	}
	free_pointers(1, var);
	return (NULL);
}

/*
** SYNOPSIS: saves new environment variable.
*/
void
	set_new_var(char *var, t_arguments *arg)
{
	char	*temp_args[3];

	temp_args[0] = "nothing";
	temp_args[1] = var;
	temp_args[2] = NULL;
	export_new_variables(temp_args, arg);
}
/*
** SYNOPSIS: changes the values of 'OLDPWD' and 'PWD' variables.
*/
void
	renew_pwds(t_arguments *arg, char *old_path)
{
	char	*cur_path;
	char	*cwd;

	delete_env_var(arg, 7, "OLDPWD=");
	set_new_var(old_path, arg);
	cwd = getcwd(NULL, 0);
	cur_path = ft_strjoin("PWD=", cwd);
	free_pointers(1, cwd);
	delete_env_var(arg, 4, "PWD=");
	set_new_var(cur_path, arg);
}

/*
** SYNOPSIS: gets correct path depending of the argument
** passed to cd  command ('--' or '~').
*/
void
	get_paths(char **args, t_arguments *arg, char **path, char **old_path)
{
	char	*cwd;

	(*path) = NULL;
	cwd = getcwd(NULL, 0);
	(*old_path) = ft_strjoin("OLDPWD=", cwd);
	free_pointers(1, cwd);
	if (!args[1] || !ft_memcmp(args[1], "~", 2) || !ft_memcmp(args[1], "--", 3))
		(*path) = get_env_var(arg->envp, "HOME");
	else if (!ft_memcmp(args[1], "-", 2))
		(*path) = get_env_var(arg->envp, "OLDPWD");
	else
		(*path) = args[1];
}

/*
** SYNOPSIS: builtin cd command.
*/
int
	msh_cd(char **args, t_arguments *arg)
{
	char	*path;
	char	*old_path;

	if (get_arr_len(args) > 2)
	{
		ft_putstr_fd("msh: cd: too many arguments\n", 1);
		set_status(arg, 1);
		return (2);
	}
	get_paths(args, arg, &path, &old_path);
	if (chdir(path) != 0)
	{
		perror("msh");
		free_pointers(2, path, old_path); //check it with wrong directory
		set_status(arg, 1);
	}
	else
	{
		free_pointers(1, path);
		renew_pwds(arg, old_path);
		set_status(arg, 0);
	}
	return (1);
}
