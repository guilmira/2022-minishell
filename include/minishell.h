/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 07:43:14 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/13 12:23:01 by guilmira         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

//if your library DOESNT work try uncommenting this:
//#include "/usr/include/readline/readline.h"
//#include "/usr/include/readline/history.h"

# include <limits.h>
# include <stdarg.h>

/* LIBFT */
# include "../libft_submodule/0includes/libft.h"

/* TOKENS*/
# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a"

/* Global variables and structs*/

/* Struct that stores command data. */
typedef struct s_command
{
	char	*path;
	char	**command;
}			t_command;

/* Struct that stores the data kept between loops. */
typedef struct s_program
{
	char	**envp;
	int		status;
	char	**builtin_str;
}	t_prog;

/* Struct that stores arguments and program parameters. */
typedef struct s_arguments
{
	char	**argv;
	char	**tabla_temp;
	int		flag_execution;
	int		command_number;
	int		total_commands;
	int		*fds;
	int		flag_file_in;
	int		flag_file_out;
	char	*file_input;
	char	*file_output;
	int		(*builtin_func[8])(char **, struct s_arguments *);
	char	**envp;
	char	**builtin_str;
	int		status;
	t_list	*commands_lst;
	t_prog	*prog;
}			t_arguments;

/* Protoypes minishell builtins. */
int			msh_echo(char **args, t_arguments *arg);
int			msh_cd(char **args, t_arguments *arg);
int			msh_pwd(char **args, t_arguments *arg);
int			msh_export(char **args, t_arguments *arg);
int			msh_unset(char **args, t_arguments *arg);
int			msh_env(char **args, t_arguments *arg);
int			msh_exit(char **args, t_arguments *arg);
int			msh_help(char **args, t_arguments *arg);
int			msh_num_builtins(t_arguments *arg);
void		ft_str_arr_sort(char *arr[], unsigned int len);
void		print_str_arr(char *const *arr, int fd);
size_t		get_arr_len(char **arr);
void		**get_arr(size_t elem_num, size_t elem_size);
void		copy_arr(char **dest, char **src, size_t src_len);
int			count_chars(char *p, char *needle);
void		delete_env_var(t_arguments *arg, size_t len, const char *tmp);
void		export_new_variables(char **args, t_arguments *arg);
void		export_multi_var(char *const *args, int i,
				 size_t envp_len, char **new_envp);
void		loop_and_print_echo_args(char **args, t_arguments *arg, int i);
char		*get_env_var(char **envp, char *needle);
void		renew_pwds(t_arguments *arg, char *old_path);
char		*ft_concat(const char *s1, const char *s2);
void		set_status(t_arguments *arg, int status);
//int			get_fd(char *path);
bool		is_within_range(const char *str);
int			atoi_exit_code(const char *str);
void		init_builtin_func_arr(int (*builtin_func[])(char **, t_arguments *));
void		init_builtins(char **builtin_str);
void		free_pointers(int num, ...);
char		*ft_strtok(char *str, const char *delim);
void		sig_handler(int signum);
void		eof_exit(t_arguments *args);
void		set_shlvl_num(t_arguments *arg);
char		*get_env_val(t_arguments *arg, size_t len, const char *tmp);

/* FILE PATHS */
# define PATH_BIN "/bin/"
# define PATH_USR "/usr/bin/"
# define FILE_NAME "outfile.txt"
# define FULL_PERMISSIONS 0777
# define RESTRICTED_PERM 777

/* ERROR MESSAGES */
# define ARG_NUMBER 1
# define TOTAL_SYMBOLS 6
# define MSHELL "msh> "
# define INVALID_ARGC "Program execution does not admit arguments\n."
# define MEM "Failed memory allocation.\n"
# define ARG "Incorrect arguments.\n"
# define LINE "Error reading the line.\n"
# define MSG "Pipe function failure.\n"
# define LST "Failure at linked list.\n"
# define FILE_ERROR "File not found or error at opening.\n"
# define FORK_ERROR "Error at fork creation\n"
# define DUP_ERROR "Dup2 function failure.\n"
# define EXE_ERROR "Execve function failure.\n"

# define PIPE "lex_PIPE"

//temporary
void printlt(char **lexer_table);
void printltt(char **table);
void printlttt(char **table, int *org);

/* Protoypes minishell reader. */

int			count_table(char **table);
/* FILES */
void		file_management(int argc, char *argv[], t_arguments *args);
/* INITIALIZATION */
t_prog		*initalize_prog(char **envp, char **builtin_str);
t_arguments	*intialize_arg(t_prog *prog);
/* PRE-FILTER */
int			pre_filter(char *line);
int			non_closed_quote(char *line, char quote);
/* PARSER */
char		*set_path(char *command, char **folders);
int			prepare_process(int fd_to_close, int fd_to_prepare);
/* LEXER */
char		**main_lexer(char *line);
int			*class_lex_table(char **lexer_table);
char		**remove_quote(char **table);
/* QUOTE MANAGEMENT */
char		**quote_management(char **table);
char		**quote_split(char const *s, char c);
/* READER */
void		arg_reader(int argc, char *argv[], char *envp[], t_arguments *args);
char		*set_path(char *command, char **folders);
void		shell_reader(char *envp[], t_arguments *args);
/* READER SPLIT COMMANDS */
char		**get_command_table(char **lexer_table, t_arguments *args, int *type);
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
void		single_son(t_arguments *args);
/* AUXILIAR */
int			file_exists(char *str);
int			*arg_descriptors(t_arguments *args);
void		*ft_lst_position(t_list *lst, int n);
/* MEMORY MGMT */
void		ft_shut(char *str, int i);
void		free_heap_memory(t_arguments *args);
void		ft_shutdown(char *str, int i, t_arguments *args);

#endif
