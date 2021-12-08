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
	char	**argv;
	char	**envp;
}	t_data;

int		msh_execute(char **args, t_data *data);
int		msh_echo(char **args, t_data *data);
int		msh_cd(char **args, t_data *data);
int		msh_pwd(char **args, t_data *data);
int		msh_export(char **args, t_data *data);
int		msh_unset(char **args, t_data *data);
int		msh_env(char **args, t_data *data);
int		msh_exit(char **args, t_data *data);
int		msh_help(char **args, t_data *data);
int		msh_num_builtins(void);
void	ft_str_sort(char *arr[], unsigned int len);
void	print_str_arr(char *const *arr);
size_t	get_arr_len(char **arr);
void	**get_arr(size_t elem_num, size_t elem_size);
void	copy_arr(char **dest, char **srs, size_t src_len);
int		count_chars(char *p, char *needle);
void	manipulate_envp(t_data *data, size_t len, const char *tmp);
void	export_new_variables(char *const *args, t_data *data);
void	export_multi_var(char *const *args, int i,
			size_t envp_len, char **new_envp);

#endif
