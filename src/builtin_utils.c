/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:36:14 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/08 14:36:15 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	manipulate_envp(t_data *data, size_t len, const char *tmp)
{
	int		i;
	char	*not_found;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], tmp, len))
		{
			data->envp[i] = NULL;
			while (data->envp[i + 1])
			{
				data->envp[i] = data->envp[i + 1];
				data->envp[i + 1] = NULL;
				i++;
			}
			return ;
		}
		i++;
	}
	not_found = ft_substr(tmp, 0, (ft_strlen(tmp) - 1));
	printf("Variable %s not found\n", not_found); //should we keep this warning?
	free(not_found);
}

void
	export_multi_var(char *const *args, int i, size_t envp_len, char **new_envp)
{
	char	*arg_copy;
	char	*line;

	arg_copy = (char *) malloc((ft_strlen(args[i]) + 1) * sizeof(char ));
	ft_strlcpy(arg_copy, args[i], ft_strlen(args[i]) + 1);
	strtok(arg_copy, "=");
	line = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(arg_copy, "="),
					"'"), (ft_strchr(args[i], '=') + 1)), "'");
	new_envp[envp_len] = line;
	free(arg_copy);
}

void
	export_new_variables(char **args, t_data *data)
{
	int		i;
	size_t	envp_len;
	char	**new_envp;
	char	*temp;

	i = 1;
	while (args[i])
	{
		envp_len = get_arr_len(data->envp);
		new_envp = (char **)get_arr(envp_len + 2, sizeof(char *));
		copy_arr(new_envp, data->envp, envp_len);
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
		data->envp = new_envp;
		i++;
	}
}
