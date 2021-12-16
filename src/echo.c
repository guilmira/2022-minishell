/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:56:48 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/16 10:56:49 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	loop_and_print_echo_args(char **args, t_arguments *arg, int i, int fd)
{
	char	*temp;

	while (args[i])
	{
		if (args[i][0] == '$')
			temp = ft_strdup(get_env_var(arg->envp, args[i] + 1) + 1);
		else
			temp = ft_strdup(args[i]);
		ft_putstr_fd(temp, fd); //change hardcoded fp
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		free(temp);
		i++;
	}
}
