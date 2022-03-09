/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 07:43:14 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 13:29:11 by guilmira         ###   ########.fr       */
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

# include <limits.h>
# include <stdarg.h>

/* LIBFT */
# include "../libft_submodule/0includes/libft.h"

/* Global variables and structs*/
int	g_rv;

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
	char	**lenvp;
	int		status;
	char	**builtin_str;
}	t_prog;

/* Struct that stores arguments and program parameters. */
typedef struct s_arguments
{
	char	**argv;
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
	char	**lenvp;
	char	**builtin_str;
	int		status;
	t_list	*commands_lst;
	t_prog	*prog;
	int		*wpipe;
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
void		copy_arr_entries(char **dest, char **src, size_t n);
int			count_chars(char *p, char *needle);
void		delete_env_var(char **envp, size_t len, const char *tmp);
void		export_new_variables(char **args, t_arguments *arg);
void		export_multi_var(char *const *args, int i, \
			size_t envp_len, char **new_envp);
void		loop_and_print_echo_args(char **args, t_arguments *arg, int i);
char		*get_env_var(char **envp, char *needle, bool do_expand);
void		renew_pwds(t_arguments *arg, char *old_path);
char		*ft_concat(const char *s1, const char *s2);
void		set_status(t_arguments *arg, int status);
bool		is_within_range(const char *str);
int			atoi_exit_code(const char *str);
void		init_builtin_func_arr(int (*builtin_func[])(char **, \
			t_arguments *));
void		init_builtins(char **builtin_str);
void		free_pointers(int num, ...);
char		*ft_strtok(char *str, const char *delim);
void		sig_handler(int signum);
void		eof_exit(t_arguments *args);
void		set_shlvl_num(t_arguments *arg);
char		*get_env_val(t_arguments *arg, size_t len, const char *tmp);
char		**copy_array(char **dest, char **src, unsigned int extra_cells);
char		*ft_multistr_concat(int count, ...);
char		*find_tail(char **args, int i);
char		*find_head(char **args, t_arguments *arg, int i, const char *tail);
size_t		get_envv_len(const char *s);
void		mnge_heredoc(t_command *command_struct);
void		set_signal(int sig_type);
int			heredoc_routine(t_command *command_struct);
bool		var_have_val(char **envp, char *needle);
bool		export_new_l_variables(char **args, t_arguments *arg);
void		set_new_var(char *var, t_arguments *arg);
void		expand_l_var(char **args, t_arguments *arg, int i, char *temp);
void		get_rid_of_quotes(char **args, size_t i, char *str);
bool		is_valid_var(char *const *args, t_arguments *arg, int i);
char		*get_env_var_body(char **envp, bool do_expand, int i, int len);
char		*get_path(t_command *command_struct);
void		write_child_status(const t_arguments *args, int *i);
void		read_child_status(t_arguments *args);

/* FILE PATHS */
# define PATH_BIN "/bin/"
# define PATH_USR "/usr/bin/"
# define FILE_NAME "outfile.txt"
# define FULL_PERMISSIONS 0777
# define RESTRICTED_PERM 777

/* ERROR MESSAGES */
# define ARG_NUMBER 1
# define TOTAL_SYMBOLS 5
# define MAX_COMMANDS 50
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
# define IN "lex_INPUT"
# define OUT "lex_OUTPUT"
# define APPEND "lex_APPEND"
# define HEREDOC "lex_HEREDOC"
# define SINGLE '\''
# define DOUBLE '"'
# define EXPAN '$'
# define RIDDLER '?'
# define EMPTY_LINE ""

# define HEREDOC_PROMPT "> "

/* TO delete. */

/* Others. */
void		printer(char **table, int *org);
void		init_options(char **option, char **option_name);
char		*build_new_line(t_list *list);
int			ignore_symbol(char *str, int position);
void		rl_replace_line(const char *txt, int clear_undo);



/* Protoypes minishell reader. */

int			count_table(char **table);
/* FILES */
void		file_management(int argc, char *argv[], t_arguments *args);
/* INITIALIZATION */
t_prog		*initalize_prog(char **envp, char **builtin_str);
t_arguments	*intialize_arg(t_prog *prog);
/* PRE-FILTER */
int			pre_filter(char *line);
int			pre_filter_simple(char *line);
int			pre_filter_advanced(char *line);
int			quotes_filter(char *line);
int			is_one_of_lexer_symbols(char symbol);
/* PARSER */
char		*set_path(char *command, char **folders, char **envp);
int			prepare_process(int fd_to_close, int fd_to_prepare);
/* LEXER */
char		**main_lexer(char *line, t_arguments *args);
int			*class_lex_table(char **lexer_table);
char		**remove_quote(char **table);
t_list		*build_lexer_list(char *line);
/* QUOTE MANAGEMENT */
char		**quote_management(char **table);
char		**quote_split(char const *s, char c);
char		*ultra_quotes(char *str);
/* QUOTE AUXILIAR */
int			is_quote(char symbol);
char		*advance_line_quotes(char *line, char quote);
int			advance_to_next_quote(char *line, int i);
/* READER */
void		shell_reader(t_arguments *args);
void		arg_reader(char **table, t_arguments *args);
t_list		*load_linked_list(char **table, char **envp,\
			int total_commands, t_arguments *args);
void		load_command_struct(t_command *command_struct,\
			char **table, int i, t_arguments *args);
/* READER SPLIT COMMANDS */
char		**get_command_table(char **lexer_table, \
			t_arguments *args, int *type);
/* DOLLAR EXPANSION */
char		**dollar_expansion(char **table, t_arguments *args);
char		*ultra_expansion(char *str, t_arguments *args);
/* FILE REDIRECTION */
void		management_file(char **table, t_arguments *args);
void		file_setup(t_list *list_files, \
			t_list *list_type, t_arguments *args);
int			file_exists(char *str);
/* USED IN LEXER QUOTES AND IN DOLLAR EXPANSION. */
void		fix_previous_line(char *line, int t, int i, t_list **list);
/* Protoypes minishell execution. */

/* EXECUTION */
int			process_exe(t_arguments *args);
int			msh_execute(char **args, t_arguments *arguments);
/* PARENT PROCESS */
int			mid_process(t_arguments *args);
int			single_process(t_arguments *args);
/* SON PROCESS */
int			first_son(t_arguments *args);
int			last_son(int index, t_arguments *args);
int			single_son(t_arguments *args);
/* FILES AT SONS*/
void		input_form_file(char *path);
void		output_to_file(char *path);
void		output_to_file_append(char *path);
/* AUXILIAR */
int			*arg_descriptors(t_arguments *args);
void		*ft_lst_position(t_list *lst, int n);
/* MEMORY MGMT */
void		ft_shut(char *str, int i);
void		free_heap_memory(t_arguments *args);
void		ft_shutdown(char *str, int i, t_arguments *args);

#endif
