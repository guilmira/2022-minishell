/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:55:52 by asydykna          #+#    #+#             */
/*   Updated: 2022/01/05 14:20:13 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: converts string passed to exit commadn to int.
** Specific version of ft_atoi function.
*/
int
	atoi_exit_code(const char *str)
{
	int				sign;
	unsigned long	count;

	sign = 1;
	count = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13) || *str == 127)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (false);
	while (*str >= '0' && *str <= '9')
	{
		count *= 10;
		count += (*str - 48) * sign;
		str++;
	}
	if (count && count < 256)
		return ((int)count);
	else
		return ((int)count % 256);
}

/*
** SYNOPSIS: analyzes if the numeric argument passed to exit command
** is within the range of LONG_MIN and LONG_MAX.
*/
bool
	get_bool(const char *str, int sign, unsigned long count)
{
	if (*str)
		return (false);
	if ((sign == 1 && count <= LONG_MAX)
		|| (sign == -1 && count >= (unsigned long)LONG_MIN))
		return (true);
	return (false);
}

/*
** SYNOPSIS: analyzes if the argument passed to exit command is numeric.
** If the argument is numeric, it is passed to get_bool function
*/
bool
	is_within_range(const char *str)
{
	int				sign;
	unsigned long	count;

	sign = 1;
	count = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13) || *str == 127)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (false);
	while (*str >= '0' && *str <= '9')
	{
		count *= 10;
		count += (*str - 48) * sign;
		str++;
	}
	while (*str == ' ' || (*str >= 9 && *str <= 13) || *str == 127)
		str++;
	return (get_bool(str, sign, count));
}

/*
** SYNOPSIS: initializes builtin_func array.
*/
void
	init_builtins(char **builtin_str)
{
	builtin_str[0] = "echo";
	builtin_str[1] = "cd";
	builtin_str[2] = "pwd";
	builtin_str[3] = "export";
	builtin_str[4] = "unset";
	builtin_str[5] = "env";
	builtin_str[6] = "exit";
	builtin_str[7] = "help";
	builtin_str[8] = NULL;
}

/*
** SYNOPSIS: an array of function pointers (that takes two arrays
** of strings and returns an int)
*/
void
	init_builtin_func_arr(int (*builtin_func[])(char **, t_arguments *))
{
	builtin_func[0] = &msh_echo;
	builtin_func[1] = &msh_cd;
	builtin_func[2] = &msh_pwd;
	builtin_func[3] = &msh_export;
	builtin_func[4] = &msh_unset;
	builtin_func[5] = &msh_env;
	builtin_func[6] = &msh_exit;
	builtin_func[7] = &msh_help;
}
