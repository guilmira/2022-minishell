/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 07:28:06 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/08 10:39:18 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	program_loop()
{
	while (1)
	{
		printf("minishell > ");
		
	}
}

int	main(int argc, char *argv[])
{
	argc = (int) argc;
	argv = (void *) argv;
	
	program_loop();
	exit (0);
}
