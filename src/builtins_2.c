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
** TODO: arg->envp might be malloced, mind memory leaks
*/

int
	msh_env(char **args __attribute__((unused)), t_arguments *arg)
{
	print_str_arr(arg->envp, 0);
	printf("\n");
	set_status(arg, 0);
	return (1);
}


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
	if (count >= 0 && count < 256)
		return ((int)count);
	else
		return ((int)count % 256);
}

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
