/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 07:43:14 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/16 11:07:45 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* PREMADE LIBRARIES */
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

/* LIBFT */
# include "../libft_submodule/0includes/libft.h"

/* TOKENS*/
# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a"

/* Global variables and structs*/
char	*g_builtin_str[8];

/* Struct that stores command data. */
typedef struct s_command
{
	char	*path;
	char	**command;
}			t_command;

/* Struct that stores arguments and program parameters. */
typedef struct s_arguments
{
	char	**envp;
	char	**argv;
	t_list	*commands_lst;
	int		flag_file;
	int		command_number;
	int		total_commands;
	int		*fds;
	char	*file_input;
	char	*file_output;
	int		status;
}			t_arguments;

/* Protoypes minishell builtins. */
int		msh_echo(char **args, t_arguments *arg);
int		msh_cd(char **args, t_arguments *arg);
int		msh_pwd(char **args, t_arguments *arg);
int		msh_export(char **args, t_arguments *arg);
int		msh_unset(char **args, t_arguments *arg);
int		msh_env(char **args, t_arguments *arg);
int		msh_exit(char **args, t_arguments *arg);
int		msh_help(char **args, t_arguments *arg);
int		msh_num_builtins(void);
void	ft_str_arr_sort(char *arr[], unsigned int len);
void	print_str_arr(char *const *arr);
size_t	get_arr_len(char **arr);
void	**get_arr(size_t elem_num, size_t elem_size);
void	copy_arr(char **dest, char **srs, size_t src_len);
int		count_chars(char *p, char *needle);
void	delete_env_var(t_arguments *arg, size_t len, const char *tmp);
void	export_new_variables(char **args, t_arguments *arg);
void	export_multi_var(char *const *args, int i,
		size_t envp_len, char **new_envp);
void	loop_and_print_echo_args(char **args, t_arguments *arg, int i, int fd);
char	*get_env_var(char **envp, char *needle);
void	renew_pwds(t_arguments *arg, char *old_path);
char	*ft_concat(const char *s1, const char *s2);
void	set_status(t_arguments *arg, int status);

/* FILE PATHS */
# define PATH_BIN "/bin/"
# define PATH_USR "/usr/bin/"
# define FILE_NAME "outfile.txt"
# define FULL_PERMISSIONS 0777
# define RESTRICTED_PERM 777

/* ERROR MESSAGES */
# define NOT_COMMANDS 3
# define ARG_NUMBER 1
# define INVALID_ARGC "Program execution does not admit arguments\n."
# define MEM "Failed memory allocation.\n"
# define ARG "Incorrect arguments.\n"
# define MSG "Pipe function failure.\n"
# define LST "Failure at linked list.\n"
# define FILE_ERROR "File not found or error at opening.\n"
# define FORK_ERROR "Error at fork creation\n"
# define DUP_ERROR "Dup2 function failure.\n"
# define EXE_ERROR "Execve function failure.\n"

/* Protoypes minishell reader. */

/* FILES */
int			file_management(int argc, char *argv[], t_arguments *args);
/* PARSER */
char		*set_path(char *command, char **folders);
int			prepare_process(int fd_to_close, int fd_to_prepare);
/* READER */
t_arguments	*arg_reader(int argc, char *argv[], char *envp[]);
char		*set_path(char *command, char **folders);
t_arguments	*shell_reader(char *envp[]);
/* READER AUX */
int			is_pipe(char z);
int			is_command(char *str);
int			count_commands(char **argv);

/* Protoypes minishell execution. */

/* EXECUTION */
void		process_exe(t_arguments *args);
int			msh_execute(char **args, t_arguments *arguments);
/* PARENT PROCESS */
void		mid_process(t_arguments *args);
void		single_process(t_arguments *args);
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
