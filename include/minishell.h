/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 07:43:14 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/08 12:33:26 by guilmira         ###   ########.fr       */
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
void	**get_arr(int elem_num, size_t elem_size);
void	copy_arr(char **dest, char **srs, int src_len);


//parte de guille

#include <fcntl.h>

/* FILE PATHS */
# define PATH_BIN "/bin/"
# define PATH_USR "/usr/bin/"
# define FILE_NAME "outfile.txt"
# define FULL_PERMISSIONS 0777
# define RESTRICTED_PERM 777
/* ERROR MESSAGES */
# define ARGUMENTS 2
# define NOT_COMMANDS 4
# define MEM "Failed memory allocation.\n"
# define ARG "Incorrect arguments.\n"
# define MSG "Pipe function failure.\n"
# define LST "Failure at linked list.\n"
# define FILE_ERROR "File not found or error at opening.\n"
# define FORK_ERROR "Error at fork creation\n"
# define DUP_ERROR "Dup2 function failure.\n"
# define EXE_ERROR "Execve function failure.\n"

/** Struct that stores command data. */
typedef struct s_command
{
	char	*path;
	char	**command;
}			t_command;

/** Struct that stores arguments and program parameters. */
typedef struct s_arguments
{
	t_list	*commands_lst;
	int		flag_file;
	int		command_number;
	int		total_commands;
	int		*fds;
	char	*file_input;
	char	*file_output;
}			t_arguments;

void	process_exe(t_arguments *args);

/* FILES */
int			file_management(int argc, char *argv[], t_arguments *args);
/* PARSER */
int			parser(int argc, char *argv[]);
char		*set_path(char *command, char **folders);
int			prepare_process(int fd_to_close, int fd_to_prepare);
/* READER */
t_arguments	*arg_reader(int argc, char *argv[], char *envp[]);
char		*set_path(char *command, char **folders);
/* PARENT PROCESS */
void		mid_process(t_arguments *args);
/* SON PROCESS */
void		first_son(t_arguments *args);
void		last_son(int index, t_arguments *args);
/* AUXILIAR */

int			file_exists(char *str);
int			*arg_descriptors(t_arguments *args);
void		*ft_lst_position(t_list *lst, int n);

/* MEMORY MGMT */
void		ft_shut(char *str, int i);
void		free_heap_memory(t_arguments *args);
void		ft_shutdown(char *str, int i, t_arguments *args);


#endif
