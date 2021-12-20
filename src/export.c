/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:15:59 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/17 11:16:00 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	free_pointers(1, arg_copy);
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

int
	msh_export(char **args, t_arguments *arg)
{
	int		envp_len;
	char	**arr;
	size_t	args_len;
	int		fd;

	fd = get_fd(arg->file_output);
	args_len = get_arr_len(args);
	if (args_len == 1)
	{
		envp_len = (int)get_arr_len(arg->envp);
		arr = (char **)get_arr(envp_len + 1, sizeof(char *));
		copy_arr(arr, arg->envp, envp_len);
		arr[envp_len] = NULL;
		ft_str_arr_sort(arr, envp_len);
		print_str_arr(arr, fd);
		ft_putendl_fd("", fd);
		free_pointers(1, arr);
	}
	else
		export_new_variables(args, arg);
	set_status(arg, 0);
	return (1);
}
