/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:18:55 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 14:04:37 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_error(void)
{
	perror("Pipe creation failed");
	exit(EXIT_FAILURE);
}

static void	free_env_vars_from_child(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	return ;
}

void	allocate_pipe_memory(t_shell *p)
{
	int	i;

	i = 0;
	p->pipes = (int **)malloc(p->nr_cmds * sizeof(int *));
	p->pid = (pid_t *)malloc(p->nr_cmds * sizeof(pid_t));
	if (!p->pipes || !p->pid)
		ft_malloc_error();
	while (i < p->nr_cmds)
	{
		p->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!p->pipes[i])
			ft_malloc_error();
		if (pipe(p->pipes[i]) == -1)
			pipe_error();
		i++;
	}
}

static char	*find_path_in_env(t_env_list *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			return (ft_strdup(env->value));
			break ;
		}
		env = env->next;
	}
	return (NULL);
}

static void	free_split_paths(char **split_paths, char *path)
{
	int	i;

	i = 0;
	while (split_paths[i] != NULL)
	{
		free(split_paths[i]);
		i++;
	}
	free(split_paths);
	free(path);
}

static void	set_cmd_path(t_lst *cmd)
{
	cmd->cmd_path = ft_strdup(cmd->content);
}

int	find_path(t_lst *cmd, t_env_list *env, int i)
{
	char	*path;
	char	**split_paths;
	char	*part_p_with_slash;

	if (cmd->content[0] == '/' || cmd->content[0] == '.')
		return (set_cmd_path(cmd), 0);
	path = find_path_in_env(env);
	if (path == NULL)
		return (set_cmd_path(cmd), 0);
	split_paths = ft_split(path, ':');
	while (split_paths[++i])
	{
		part_p_with_slash = ft_strjoin(split_paths[i], "/");
		cmd->cmd_path = ft_strjoin(part_p_with_slash, cmd->content);
		free(part_p_with_slash);
		if (access(cmd->cmd_path, X_OK) == 0)
			break ;
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	return (free_split_paths(split_paths, path), 1);
}

/* This function set the redirection for each command */
void	set_redirection(t_lst *cmd, t_shell *p, int i)
{
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (i > 0 && cmd->prev->run == false)
		dup2(p->null_fd, STDIN_FILENO);
	else if (i > 0 && p->prev_pipe >= 0)
		dup2(p->prev_pipe, STDIN_FILENO);
	else
		dup2(0, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else if (cmd->next != NULL && p->pipes[i][1] >= 0)
		dup2(p->pipes[i][1], STDOUT_FILENO);
	else
		dup2(1, STDOUT_FILENO);
}

void	close_all_pipes(t_shell *p)
{
	int	i;

	i = 0;
	while (i < p->nr_cmds)
	{
		close(p->pipes[i][0]);
		close(p->pipes[i][1]);
		i++;
	}
}

char	**concatenate_key_value(t_env_list *list, int size)
{
	char		**result;
	t_env_list	*temp;
	int			i;

	result = (char **)malloc((size + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	temp = list;
	i = 0;
	while (temp)
	{
		size = ft_strlen(temp->key) + ft_strlen(temp->value) + 1;
		result[i] = (char *)malloc((size + 1) * sizeof(char));
		if (!result[i])
		{
			free(result);
			return (NULL);
		}
		ft_strlcpy(result[i], temp->key, size);
		ft_strlcat(result[i], "=", size);
		ft_strlcat(result[i++], temp->value, size + 1);
		temp = temp->next;
	}
	result[i] = NULL;
	return (result);
}

/* This function assigns redirection, closes pipes, and calls execve() */
void	execute_child(t_shell *p, t_lst *cmd, int i)
{
	char	**env_list;

	env_list = NULL;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_redirection(cmd, p, i);
	if (handle_build_in(p, cmd) != -1)
	{
		free_all_memory(p);
		exit(EXIT_SUCCESS);
	}
	find_path(cmd, p->envir, -1);
	env_list = concatenate_key_value(p->envir, env_lstsize(p->envir));
	close_all_pipes(p);
	execve(cmd->cmd_path, cmd->args, env_list);
	free_env_vars_from_child(env_list);
	exit(error_execve(cmd->args[0], p));
}

void	execute_parent(t_shell *p, t_lst *cmd, int i)
{
	int	stat_loc;
	int	exit_status;
	int	j;

	close(p->pipes[i][1]);
	p->prev_pipe = p->pipes[i][0];
	if (i == p->nr_cmds - 1)
		close(p->prev_pipe);
	if (i == p->nr_cmds - 1)
	{
		waitpid(p->pid[i], &stat_loc, 0);
		if (WIFEXITED(stat_loc))
		{
			exit_status = WEXITSTATUS(stat_loc);
			p->command_status = exit_status;
		}
		j = -1;
		while (++j < i)
			close(p->pipes[j][0]);
	}
	(void)cmd;
}

/* Execution of multiple commands using forks */
bool	execute_commands(t_shell *p, t_lst *cmd, int i)
{
	t_lst	*current;

	current = cmd;
	allocate_pipe_memory(p);
	while (++i < p->nr_cmds)
	{
		p->command_status = infile(current);
		if (outfile(current) && current->run == true)
		{
			p->pid[i] = fork();
			if (p->pid[i] == -1)
				ft_fork_error();
			if (p->pid[i] == 0)
				execute_child(p, current, i);
			else
				execute_parent(p, current, i);
		}
		current = current->next;
	}
	i = 0;
	while (i++ < p->nr_cmds - 1)
		wait(NULL);
	free_allocation_malloc_pipes(p);
	return (true);
}

void	execute(t_shell *p)
{
	t_lst	*current;

	current = p->token_list;
	p->nr_cmds = count_cmd(current);
	if (p->nr_cmds == 1 && is_build_in_cmd(current) == true)
		p->command_status = handle_build_in(p, current);
	else
		execute_commands(p, current, -1);
	signal(SIGINT, handle_sigint);
}
