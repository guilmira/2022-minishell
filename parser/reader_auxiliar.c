/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_auxiliar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:46:01 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/04 12:07:58 by guilmira         ###   ########.fr       */
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

/** PURPOSE : Checks whether command is one of the 
 * so called "specials" which have text after the command itself
 * i.e : echo "hola", cd ".." and others. */
int	is_special(char *str)
{
	int		i;
	int		number_complex;
	char	*complex[7];

	number_complex = 7;
	if (!str)
		return (0);
	i = -1;
	init_complex(complex);
	while (++i < number_complex - 1)
		if (!ft_strcmp(str, complex[i]))
			return (1);
	return (0);
}
