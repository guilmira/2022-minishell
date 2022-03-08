/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:15:59 by asydykna          #+#    #+#             */
/*   Updated: 2022/02/17 14:19:37 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: called if the argument passed to export command contains '='.
*/
void
	export_multi_var(char *const *args, int i, size_t envp_len, char **new_envp)
{
	char	*arg_copy;
	char	*line;

	arg_copy = (char *) malloc((ft_strlen(args[i]) + 1) * sizeof(char ));
	ft_strlcpy(arg_copy, args[i], ft_strlen(args[i]) + 1);
	ft_strtok(arg_copy, "=");
	line = ft_multistr_concat(5, arg_copy, "=", "'",
			(ft_strchr(args[i], '=') + 1), "'");
	new_envp[envp_len] = line;
	free_pointers(1, arg_copy);
}

void
	replace_envp(t_arguments *arg, char **new_envp)
{
	ft_free_split(arg->envp);
	arg->envp = new_envp;
}

void
	export_new_vars_cont(char **args, int i, size_t envp_len, char **new_envp)
{
	if (count_chars(args[i], "=") > 1)
		export_multi_var(args, i, envp_len, new_envp);
	else if (!new_envp[envp_len])
		new_envp[envp_len] = ft_strdup(args[i]);
}

/*
** SYNOPSIS: called if there are more than 1 argument passed to export command.
*/
void
	export_new_variables(char **args, t_arguments *arg)
{
	int		i;
	size_t	envp_len;
	char	**new_envp;
	char	*temp;
//	char	*temp2;

	i = 0;
	while (args[++i])
	{
		temp = NULL;
		if (!is_valid_var(args, arg, i))
			continue ;
		expand_l_var(args, arg, i, temp);
		//temp2 = ft_concat(args[i], "=");
		if (var_have_val(arg->envp, args[i]))
			continue ;
		delete_env_var(arg->envp, get_envv_len(args[i]), args[i]);
	//	free_pointers(1, temp2);
		envp_len = get_arr_len(arg->envp);
		new_envp = copy_array(new_envp, arg->envp, 2);
		/*if (!ft_strchr(args[i], '='))
		{
			temp = ft_multistr_concat(3, args[i], "=", "''");
			new_envp[envp_len] = temp;
		}*/
		if (ft_strchr(args[i], '=') && !(*(ft_strchr(args[i], '=') + 1)))
		{
			temp = ft_multistr_concat(2, args[i], "''");
			new_envp[envp_len] = temp;
		}
		get_rid_of_quotes(args, i, args[i]);
		export_new_vars_cont(args, i, envp_len, new_envp);
		new_envp[envp_len + 1] = NULL;
		replace_envp(arg, new_envp);
	}
}

/*
** SYNOPSIS: builtin export command.
*/
int
	msh_export(char **args, t_arguments *arg)
{
	char	**arr;
	size_t	args_len;

	args_len = get_arr_len(args);
	if (args_len == 1)
	{
		arr = NULL;
		arr = copy_array(arr, arg->envp, 1);
		ft_str_arr_sort(arr, get_arr_len(arr));
		print_str_arr(arr, 1);
		ft_free_split(arr);
	}
	else
		export_new_variables(args, arg);
	set_status(arg, 0);
	return (1);
}
