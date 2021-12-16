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

char *
	find_tail(char **args, int i)
{
	char	*tail;

	if (ft_strchr(args[i], '='))
		tail = ft_strdup(ft_strchr(args[i], '='));
	else
		tail = NULL;
	return (tail);
}

char *
	find_head(char **args, t_arguments *arg, int i, const char *tail)
{
	char	*head;
	size_t	var_len;

	if (tail)
	{
		var_len = ft_strchr(args[i], '=') - (args[i] + 1);
		head = get_env_var(arg->envp, ft_substr(args[i] + 1, 0, var_len));
	}
	else
		head = get_env_var(arg->envp, args[i] + 1);
	return (head);
}

void
	loop_and_print_echo_args(char **args, t_arguments *arg, int i, int fd)
{
	char	*head;
	char	*tail;

	while (args[i])
	{
		if (args[i][0] == '$')
		{
			if (args[i][1] == '?')
			{
				ft_putnbr_fd(arg->status, fd);
				return ;
			}
			tail = find_tail(args, i);
			head = find_head(args, arg, i, tail);
		}
		else
			head = ft_strdup(args[i]);
		ft_putstr_fd(head, fd); //change hardcoded fp
		if (tail)
			ft_putstr_fd(tail, fd);
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		free(head);
		if (tail)
		{
			free(tail);
			tail = NULL;
		}
		i++;
	}
	set_status(arg, 0);
}

int
	msh_echo(char **args, t_arguments *arg)
{
	int		i;
	bool	have_option;
	int		fd;

	i = 1;
	have_option = false;
	if (!ft_memcmp(args[i], "-n", 3)) //what is the args[1] == NULL?
	{
		have_option = true;
		i += 1;
	}
	if (arg->flag_file)
	{
		fd = fileno(fopen(arg->file_output, "w"));
		if (fd < 0)
		{
			perror("msh: "); //needs to be tested
			return (1);
		}
	}
	else
		fd = 1;
	loop_and_print_echo_args(args, arg, i, fd);
	if (!have_option)
		ft_putstr_fd("\n", fd);
	return (1);
}
