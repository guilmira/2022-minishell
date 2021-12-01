/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 07:43:14 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/30 14:02:43 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


/* COMMENTS */
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>

# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a"

int	msh_execute(char **args);
int	msh_cd(char **args);
int	msh_help(char **args);
int	msh_exit(char **args);

#endif
