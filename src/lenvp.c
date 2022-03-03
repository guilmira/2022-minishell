/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:44 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/02 12:52:45 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	delete_lenv_var(t_arguments *arg, size_t len, const char *tmp)
{
	int		i;
	char	*tmp2;

	i = 0;
	while (arg->lenvp[i])
	{
		if (!ft_strncmp(arg->lenvp[i], tmp, len))
		{
			tmp2 = arg->lenvp[i];
			arg->lenvp[i] = NULL;
			free_pointers(1, tmp2);
			while (arg->lenvp[i + 1])
			{
				arg->lenvp[i] = arg->lenvp[i + 1];
				arg->lenvp[i + 1] = NULL;
				i++;
			}
			return ;
		}
		i++;
	}
}

void
	export_new_l_vars_cont(char **args, int i, size_t envp_len, char **new_envp)
{
	if (count_chars(args[i], "=") > 1)
		export_multi_var(args, i, envp_len, new_envp);
	else if (!new_envp[envp_len])
		new_envp[envp_len] = ft_strdup(args[i]);
}

bool
	export_new_l_variables(char **args, t_arguments *arg)
{
	int		i;
	size_t	lenvp_len;
	char	**new_lenvp;
	bool	ret;

	ret = false;
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '$'))
			continue ;
		if (!ft_strchr(args[i], '='))
			continue ;
		ret = true;
		delete_lenv_var(arg, get_envv_len(args[i]), args[i]);
		lenvp_len = get_arr_len(arg->lenvp);
		new_lenvp = copy_array(new_lenvp, arg->lenvp, 2);
		export_new_l_vars_cont(args, i, lenvp_len, new_lenvp);
		new_lenvp[lenvp_len + 1] = NULL;
		ft_free_split(arg->lenvp);
		arg->lenvp = new_lenvp;
		i++;
	}
	return (ret);
}
