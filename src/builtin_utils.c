/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:36:14 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 12:07:59 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	delete_env_var(t_arguments *arg, size_t len, const char *tmp)
{
	int		i;

	i = 0;
	while (arg->envp[i])
	{
		if (!ft_strncmp(arg->envp[i], tmp, len))
		{
			arg->envp[i] = NULL;
			while (arg->envp[i + 1])
			{
				arg->envp[i] = arg->envp[i + 1];
				arg->envp[i + 1] = NULL;
				i++;
			}
			return ;
		}
		i++;
	}
}

void
	export_multi_var(char *const *args, int i, size_t envp_len, char **new_envp)
{
	char	*arg_copy;
	char	*line;

	arg_copy = (char *) malloc((ft_strlen(args[i]) + 1) * sizeof(char ));
	ft_strlcpy(arg_copy, args[i], ft_strlen(args[i]) + 1);
	strtok(arg_copy, "="); //write your own version
	line = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(arg_copy, "="),
					"'"), (ft_strchr(args[i], '=') + 1)), "'");
	new_envp[envp_len] = line;
	free(arg_copy);
}

void
	export_new_variables(char **args, t_arguments *arg)
{
	int		i;
	size_t	envp_len;
	char	**new_envp;
	char	*temp;

	i = 1;
	while (args[i])
	{
		envp_len = get_arr_len(arg->envp);
		new_envp = (char **)get_arr(envp_len + 2, sizeof(char *));
		copy_arr(new_envp, arg->envp, envp_len);
		if (!ft_strchr(args[i], '='))
		{
			temp = ft_strjoin(ft_strjoin(args[i], "="), "''");
			new_envp[envp_len] = temp;
		}
		else if (count_chars(args[i], "=") > 1)
			export_multi_var(args, i, envp_len, new_envp);
		else
			new_envp[envp_len] = ft_strdup(args[i]);
		new_envp[envp_len + 1] = NULL;
		arg->envp = new_envp;
		i++;
	}
}

char*
	ft_concat(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1 * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}

void
	set_status(t_arguments *arg, int status)
{
	arg->status = status;
}
