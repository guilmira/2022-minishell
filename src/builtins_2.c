/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:55:52 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 10:52:59 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** TODO: data->envp might be malloced, mind memory leak
*/

void
	export_new_variables(char *const *args, t_arguments *arg)
{
	int		i;
	int		envp_len;
	char	**new_envp;

	i = 1;
	while (args[i])
	{
		envp_len = get_arr_len(arg->envp);
		new_envp = (char **)get_arr(envp_len + 2, sizeof(char *));
		copy_arr(new_envp, arg->envp, envp_len);
		new_envp[envp_len] = args[i];
		new_envp[envp_len + 1] = NULL;
		arg->envp = new_envp;
		i++;
	}
}

int
	msh_export(char **args, t_arguments *arg)
{
	int		n;
	int		i;
	char	**arr;
	size_t	args_len;

	args_len = get_arr_len(args);
	if (args_len == 1)
	{
		n = 0;
		while (arg->envp[n])
			n++;
		arr = malloc((n + 1) * sizeof(char *));
		i = 0;
		while (arg->envp[i])
		{
			arr[i] = arg->envp[i];
			i++;
		}
		arr[i] = NULL;
		ft_str_sort(arr, n);
		print_str_arr(arr);
		printf("\n");
		free(arr);
	}
	else
		export_new_variables(args, arg);
	return (1);
}

void
	manipulate_envp(t_arguments *arg, size_t len, const char *tmp)
{
	int		i;
	char	*not_found;

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
			break ;
		}
		i++;
	}
	not_found = ft_substr(tmp, 0, (ft_strlen(tmp) - 1));
	printf("Variable %s not found\n", not_found);
	free(not_found);
}

int
	msh_unset(char **args __attribute__((unused)), t_arguments *arg)
{
	int		i;
	size_t	len;
	char	*tmp;

	i = 1;
	while (args[i])
	{
		tmp = ft_strjoin(args[i], "=");
		len = ft_strlen(tmp);
		manipulate_envp(arg, len, tmp);
		i++;
	}
	free(tmp);
	return (1);
}

int
	msh_env(char **args __attribute__((unused)), t_arguments *arg)
{
	print_str_arr(arg->envp);
	printf("\n");
	return (1);
}

int
	msh_exit(char **args __attribute__((unused)), t_arguments *arg __attribute__((unused)))
{
	return (0);
}
