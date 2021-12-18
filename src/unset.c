/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:26:31 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/17 11:26:32 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	msh_unset(char **args, t_arguments *arg)
{
	int		i;
	size_t	len;
	char	*tmp;
	int		fd;

	fd = get_fd(arg->file_output);
	if (get_arr_len(args) < 2)
		ft_putendl_fd("unset: not enough arguments", fd);
	else
	{
		i = 1;
		while (args[i])
		{
			tmp = ft_strjoin(args[i], "=");
			len = ft_strlen(tmp);
			delete_env_var(arg, len, tmp);
			free(tmp);
			i++;
		}
	}
	set_status(arg, 0);
	return (1);
}
