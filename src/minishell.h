/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:24:07 by mtocu             #+#    #+#             */
/*   Updated: 2024/06/19 15:55:08 by mtocu            ###   ########.fr       */
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
# include <stdbool.h>
#include <signal.h>
# include "../lib/libft.h"


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
	int		fd;
	char	*name; // name of the file
	t_token	token;
	struct s_file *next;
	struct s_file *prev;
}			t_file;

typedef struct s_lst //linked lists of tokens and args
{
	char				*content;
	t_token				token; //enum tokens
	t_cmd_structure		type;  //enum operators 
	t_file				*infile;
	t_file				*outfile;
	struct s_lst		*next;
	struct s_lst 		*prev;
	char				**args;
	bool				remove;
}						t_lst;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
	struct s_env_list	*prev;
	bool				to_remove;

}			t_env_list;

typedef struct s_shell // stuctura
{
	char				prompt[128];
	char				*input; // not used yet
	char				*cwd[1024]; // current working directory
	pid_t				pid;
	int					fd[2];
	int					fd_in;
	int					fd_out;
	t_lst				*token_list; // linked lists of tokens
	t_env_list			*envir; //lists of environments

	bool				error;
	
}				t_shell;


void		init(t_shell *p, char **envp, int argc, char **argv);
t_lst 		*split_into_tokens(char *line, t_shell *p);
void		manage_input(t_shell *p);

// char		*find_path(char *cmd, char **envp);
// void		execute(char *argv, char **envp);

/*create and manage the lists*/
void		lstadd_back(t_lst **lst, t_lst *new);
t_lst		*lstnew(char *content, t_token token);

/*free main list and args*/
void		free_allocation_malloc(t_lst **nodes, char *line);
void		cleaning_args(t_lst **nodes);

//void	init_env(t_shell *p, char **envp); // init env list
t_env_list	*env_lstnew(char *value, char *key);
void		free_allocation_malloc_env(t_env_list **nodes); // free all env
void		print_list(t_lst *nodes);
void		print_env(t_env_list *nodes);
void		set_command_structure(t_lst *node, bool found_cmd); //find CMD ARG and Operators for INFILE and OUTFILE

void		find_redirections(t_lst *node);
int			assign_redirection(t_lst *node, t_lst *command);
t_lst		*find_closer_command(t_lst *command);

/*managing file list*/
t_file		*file_lstnew(t_token token, char *name, int fd);
void		file_lstadd_back(t_file **list_of_files, t_file *new_file);
int			file_lstsize(t_file *list);

bool		is_infile_redirection(t_lst *current);
bool		is_outfile_redirection(t_lst *current);
void		print_list_cmd(t_lst *nodes);

/*Signals*/
void setup_signal_handlers(void);
void handle_eof(void);

#endif
