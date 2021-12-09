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

int
	msh_unset(char **args __attribute__((unused)), t_data *data)
{
	int		i;
	size_t	len;
	char	*tmp;

	if (get_arr_len(args) < 2)
		printf("unset: not enough arguments\n");
	else
	{
		i = 1;
		while (args[i])
		{
			tmp = ft_strjoin(args[i], "=");
			len = ft_strlen(tmp);
			manipulate_envp(data, len, tmp);
			i++;
		}
		free(tmp);
	}
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
