/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:39:09 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/14 13:39:10 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char *
	get_env_var(char **envp, char *needle)
{
	char	*var;
	int		i;
	int		len;

	var = NULL;
	len = ft_strlen(needle);
	i = 0;
	while (envp[i])
	{
		if (!ft_memcmp(envp[i], needle, len))
		{
			var = ft_strdup(envp[i] + len);
		}
		i++;
	}
	return (var);
}
