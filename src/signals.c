/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:47:02 by asydykna          #+#    #+#             */
/*   Updated: 2022/01/11 18:47:11 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	sig_handler(int signum __attribute__((unused)))
{
	ft_putendl_fd("", 2);
	ft_putstr_fd("msh> ", 2);
}
