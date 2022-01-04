/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_auxiliar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:46:01 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/04 11:39:11 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



static void	init_complex(char **complex)
{
	complex[0] = "echo";
	complex[1] = "cd";
	complex[2] = "cat"; //en duda
	complex[3] = "export";//en duda
	complex[4] = "man";
	complex[5] = "env"; //en duda
	complex[6] = NULL;
}

int	is_special(char *str)
{
	int	i;
	int number_complex;
	number_complex = 7;
	char		*complex[7];

	if (!str)
		return (0);
	i = -1;
	
	init_complex(complex);
	while (++i < number_complex - 1)
		if (!ft_strcmp(str, complex[i]))
			return (1);
	return (0);
}







/** PURPOSE : Count total number of tokens. */
int	count_tokens(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (argv[++i])
		j++;
	return (j);
}