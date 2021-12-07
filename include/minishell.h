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

/*
** COMMENTS
*/
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include "../libft_submodule/0includes/libft.h"

# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a"

//an array of builtin command names
char	*g_builtin_str[8];

typedef struct s_data
{
	char **argv;
	char **envp;
}	t_data;

int		msh_execute(char **args, char *envp[]);
int		msh_echo(char **args, char *envp[]);
int		msh_cd(char **args, char *envp[]);
int		msh_pwd(char **args, char *envp[]);
int		msh_export(char **args, char *envp[]);
int		msh_unset(char **args, char *envp[]);
int		msh_env(char **args, char *envp[]);
int		msh_exit(char **args, char *envp[]);
int		msh_help(char **args, char *envp[]);
int		msh_num_builtins(void);
void	ft_str_sort(char *arr[], unsigned int len);
void	print_str_arr(char *const *arr);

#endif
