/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:40:17 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/17 12:14:17 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: called if argument passed to exit command is not numeric.
*/
void
	manage_no_numeric_arg(char **args, t_arguments *arg)
{
	set_status(arg, ENOENT);
	ft_putstr_fd("msh: exit: ", 1);
	ft_putstr_fd(args[1], 1);
	ft_putendl_fd(": numeric argument required", 1);
}

bool
	contains_chars(char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			str++ ;
		else
			return (true);
	}
	return (false);
}

/*
** SYNOPSIS: builtin exit command.
*/
int
	msh_exit(char **args, t_arguments *arg)
{
	printf("exit\n");
	set_status(arg, 0);
	if (!args[1])
		return (0);
	if (contains_chars(args[1]) || !is_within_range(args[1]))
	{
		manage_no_numeric_arg(args, arg);
		return (0);
	}
	if (get_arr_len(args) > 2)
	{
		set_status(arg, EPERM);
		ft_putendl_fd("msh: exit: too many arguments", 1);
		return (1);
	}
	set_status(arg, atoi_exit_code(args[1]));
	return (0);
}
