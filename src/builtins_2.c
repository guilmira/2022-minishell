/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:55:52 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/03 17:56:01 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** TODO: data->envp might be malloced, mind memory leak
*/

void
	export_new_variables(char *const *args, t_data *data)
{
	int		i;
	int		envp_len;
	char	**new_envp;

	i = 1;
	while (args[i])
	{
		envp_len = get_arr_len(data->envp);
		new_envp = (char **)get_arr(envp_len + 2, sizeof(char *));
		copy_arr(new_envp, data->envp, envp_len);
		new_envp[envp_len] = args[i];
		new_envp[envp_len + 1] = NULL;
		data->envp = new_envp;
		i++;
	}
}

int
	msh_export(char **args, t_data *data)
{
	int		n;
	int		i;
	char	**arr;
	size_t	args_len;

	args_len = get_arr_len(args);
	if (args_len == 1)
	{
		n = 0;
		while (data->envp[n])
			n++;
		arr = malloc((n + 1) * sizeof(char *));
		i = 0;
		while (data->envp[i])
		{
			arr[i] = data->envp[i];
			i++;
		}
		arr[i] = NULL;
		ft_str_sort(arr, n);
		print_str_arr(arr);
		printf("\n");
		free(arr);
	}
	else
		export_new_variables(args, data);
	return (1);
}

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
			break ;
		}
		i++;
	}
	not_found = ft_substr(tmp, 0, (ft_strlen(tmp) - 1));
	printf("Variable %s not found\n", not_found);
	free(not_found);
}

int
	msh_unset(char **args __attribute__((unused)), t_data *data)
{
	int		i;
	size_t	len;
	char	*tmp;

	i = 1;
	while (args[i])
	{
		tmp = ft_strjoin(args[i], "=");
		len = ft_strlen(tmp);
		manipulate_envp(data, len, tmp);
		i++;
	}
	free(tmp);
	return (1);
}

int
	msh_env(char **args __attribute__((unused)), t_data *data)
{
	print_str_arr(data->envp);
	printf("\n");
	return (1);
}

int
	msh_exit(char **args __attribute__((unused)), t_data *data __attribute__((unused)))
{
	return (0);
}
