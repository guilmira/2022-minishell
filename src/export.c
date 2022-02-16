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

/*
** SYNOPSIS: calculates the length of a variable up to the "=" sign.
*/
size_t
	get_envv_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

/*
** SYNOPSIS: allows to get rid of quotes in the beginning and
** at the end of environmental variable.
*/
void
	get_rid_of_quotes(char **args, size_t i, char *str)
{
	char	*tmp;
	size_t	len;
	size_t	j;

	if (ft_strchr(str, '=') && (*(ft_strchr(str, '=') + 1) == '\''
			|| *(ft_strchr(str, '=') + 1) == '\"'))
	{
		len = ft_strlen(str);
		tmp = (char *)malloc(len - 1 * sizeof(char));
		j = -1;
		while (str[++j] != '=')
			tmp[j] = str[j];
		tmp[j] = str[j];
		j++;
		while (j + 1 < len - 1)
		{
			tmp[j] = str[(j + 1)];
			j++;
		}
		tmp[len - 2] = '\0';
		free(args[i]);
		args[i] = tmp;
	}
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

	i = 0;
	while (args[++i])
	{
		delete_env_var(arg, get_envv_len(args[i]), args[i]);
		envp_len = get_arr_len(arg->envp);
		new_envp = (char **)get_arr(envp_len + 2, sizeof(char *));
		copy_arr_entries(new_envp, arg->envp, envp_len);
		new_envp[envp_len] = NULL;
		if (!ft_strchr(args[i], '='))
		{
			temp = ft_multistr_concat(3, args[i], "=", "''");
			new_envp[envp_len] = temp;
		}
		get_rid_of_quotes(args, i, args[i]);
		if (count_chars(args[i], "=") > 1)
			export_multi_var(args, i, envp_len, new_envp);
		else if (!new_envp[envp_len])
		{
			new_envp[envp_len] = ft_strdup(args[i]);
			free_pointers(1, args[i]);
		}
		new_envp[envp_len + 1] = NULL;
		ft_free_split(arg->envp);
		arg->envp = new_envp;
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
		arr = copy_array(arr, arg->envp);
		ft_str_arr_sort(arr, get_arr_len(arr));
		print_str_arr(arr, 1);
		ft_free_split(arr);
	}
	else
		export_new_variables(args, arg);
	set_status(arg, 0);
	return (1);
}
