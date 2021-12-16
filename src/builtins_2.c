/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:55:52 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 11:38:56 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** TODO: data->envp might be malloced, mind memory leak
*/

int
	msh_export(char **args, t_arguments *arg)
{
	int		envp_len;
	char	**arr;
	size_t	args_len;

	args_len = get_arr_len(args);
	if (args_len == 1)
	{
		envp_len = (int)get_arr_len(arg->envp);
		arr = (char **)get_arr(envp_len + 1, sizeof(char *));
		copy_arr(arr, arg->envp, envp_len);
		arr[envp_len] = NULL;
		ft_str_arr_sort(arr, envp_len);
		print_str_arr(arr);
		printf("\n");
		free(arr);
	}
	else
		export_new_variables(args, arg);
	set_status(arg, 0);
	return (1);
}

int
	msh_unset(char **args, t_arguments *arg)
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
			delete_env_var(arg, len, tmp);
			i++;
		}
		free(tmp);
	}
	set_status(arg, 0);
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
	msh_exit(char **args, t_arguments *arg __attribute__((unused)))
{
	set_status(arg, 0);
	if (!args[1])
		return (0);
	if (!ft_atoi(args[1]))
	{
		ft_putstr_fd("msh: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (1);
	}
	if (get_arr_len(args) > 2)
	{
		ft_putendl_fd("msh: exit: too many arguments", 2);
		return (1);
	}
	return (0);
}
