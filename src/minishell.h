/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:24:07 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 13:50:50 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h> // for readline and print
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h> // for malloc
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "../lib/libft.h"
# include <signal.h>
# include <termios.h>
# include <dirent.h>

typedef enum e_token
{
	VAR ,
	WORD = 's',
	DLESS = 174,
	DGREAT = 175,
	LESS = '<',
	GREAT = '>',
	PIPE = '|',
	SQUOTE = '\'',
	DQUOTE = '\"',
	O_BRAKET = '(',
	C_BRAKET = ')',
}	t_token;

typedef enum e_cmd_structure
{
	CMD,
	ARG,
	INFILE,
	OUTFILE,
	OPERATOR
}			t_cmd_structure;

typedef struct s_file
{
	int					fd;
	char				*name;
	t_token				token;
	struct s_file		*next;
	struct s_file		*prev;
}			t_file;

//linked lists of tokens and args
typedef struct s_lst
{
	char				*content;
	t_token				token; //enum tokens
	t_cmd_structure		type;//enum operators 
	t_file				*infile;
	t_file				*outfile;
	struct s_lst		*next;
	struct s_lst		*prev;
	char				**args;
	char				*cmd_path;
	bool				remove;
	int					fd_in;
	int					fd_out;
	bool				run;
}						t_lst;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
	struct s_env_list	*prev;
	bool				to_remove;

}			t_env_list;

typedef struct s_shell
{
	int					fd[2];
	bool				run;
	t_lst				*token_list;
	t_env_list			*envir;
	bool				error;
	int					command_status;
	int					nr_cmds;
	int					**pipes;
	int					prev_pipe;
	int					null_fd;
	pid_t				*pid;
	char				*line;
}				t_shell;

void					init(t_shell *p, char **envp, int argc, char **argv);
t_lst					*split_into_tokens(char *line, t_shell *p);
void					manage_input(t_shell *p, int i, int arg_count);

/*create and manage the lists*/
void					lstadd_back(t_lst **lst, t_lst *new);
t_lst					*lstnew(char *content, t_token token);

/*free main list and args*/
void					free_allocation_malloc(t_lst **nodes, char *line);
void					cleaning_args(t_lst **nodes);

//void	init_env(t_shell *p, char **envp); // init env list
t_env_list				*env_lstnew(char *value, char *key);
void					env_lstadd_back(t_env_list **lst, t_env_list *new);
void					free_allocation_malloc_env(t_env_list **nodes);
void					print_list(t_lst *nodes);
void					print_env(t_env_list *nodes);

/*find CMD ARG and Operators for INFILE and OUTFILE*/
void					set_command_structure(t_lst *node, bool found_cmd);

void					find_redirections(t_lst *node, t_shell *p);
int						assign_redirection(t_lst *node, t_lst *command);
t_lst					*find_closer_command(t_lst *command);

/*managing file list*/
t_file					*file_lstnew(t_token token, char *name, int fd);
void					file_lstadd_back(t_file **list_of_files, \
							t_file *new_file);
int						file_lstsize(t_file *list);
int						env_lstsize(t_env_list *lst);
bool					is_infile_redirection(t_lst *current);
bool					is_outfile_redirection(t_lst *current);
void					print_list_cmd(t_lst *nodes);
int						count_cmd(t_lst	*nodes);

//execute functions
void					execute(t_shell *p);
int						handle_build_in(t_shell *p, t_lst *command);
char					*find_home_env(t_shell *p);
int						count_args(char	**args_from_a_node);
int						handle_cd_cmd(t_shell *p, t_lst *cmd);
bool					is_build_in_cmd(t_lst *node);
int						handle_pwd_cmd(t_shell *p, t_lst *cmd);
int						handle_exit_cmd(t_shell *p, t_lst *cmd);
int						handle_env_cmd(t_shell *p, t_lst *cmd);
int						handle_unset_cmd(t_shell *p, t_lst *cmd);
int						handle_export_cmd(t_shell *p, t_lst *cmd);
int						handle_echo_cmd(t_shell *p, t_lst *cmd);
void					find_dollar_sign_and_replace(t_shell *p);

/* Signals */
void					setup_signal_handlers(void);
void					setup_child_signal_handlers(void);
void					handle_eof(void);
void					handle_sigint(int sig);
void					sigint_child_handler(int signum);
void					sigquit_child_handler(int signum);

/*Infile and Outfile*/
int						outfile(t_lst *cmd);
int						ft_strcmp(const char *s1, const char *s2);
void					read_from_terminal(t_lst *cmd, int fd_in, \
							char *delimiter);
int						infile(t_lst *cmd);

/*Errors*/
void					ft_malloc_error(void);
void					ft_fork_error(void);
int						error_execve(char *str, t_shell *p);
void					redirection_error(t_lst *current);

//free
void					free_allocation_malloc_pipes(t_shell *p);
void					free_all_memory(t_shell *p);

#endif
