/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:18:55 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/06 16:09:39 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_error(void)
{
	perror("Pipe creation failed");
	exit(EXIT_FAILURE);
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
		if(pipe(p->pipes[i]) == -1)
			pipe_error();
		i++;
	}
}	

void	find_path(t_lst *cmd, t_env_list *env)
{
	char	*path;
	char	**split_paths;
	int		i;
	char	*part_p_with_slash;

	i = 0;
	path = NULL;
	if (cmd->content[0] == '/' || cmd->content[0] == '.')
	{
		cmd->cmd_path = ft_strdup(cmd->content);
		return ;
	}
	while (env != NULL)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0) 
		{
			path = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	split_paths = ft_split(path, ':');
	free (path);
	while (split_paths[i])
	{
		part_p_with_slash = ft_strjoin(split_paths[i], "/");
		cmd->cmd_path = ft_strjoin(part_p_with_slash, cmd->content);
		free(part_p_with_slash);
		if (access(cmd->cmd_path, X_OK) == 0)
			break ;
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
		i++;
	}
	i = 0;
	while (split_paths[i] != NULL)
	{
		free(split_paths[i]);
		i++;
	}
	free(split_paths);
}

/*This function set the redirection for each command*/
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
	else if (cmd->next != NULL && p->pipes[i][1] >= 0)// && cmd.is_last == false)
		dup2(p->pipes[i][1], STDOUT_FILENO);
	else
		dup2(1, STDOUT_FILENO);
}

/*This function assign redirection, close pipes and call execve()*/
void	execute_child(t_shell *p, t_lst *cmd, int i)
{
	char	**env_list;

	env_list = NULL;
	signal(SIGINT, SIG_DFL);//new
	signal(SIGQUIT, SIG_DFL);//new
	set_redirection(cmd, p, i);
	if(handle_build_in(p, cmd) != -1)
	{
		//free_all_memory(p); to be added
		exit(EXIT_SUCCESS);
	}
	find_path(cmd, p->envir);
	execve(cmd->cmd_path, cmd->args, NULL);//to add env list
	printf("error\n");
	exit(EXIT_FAILURE);
}

void	execute_parent(t_shell *p, t_lst *cmd, int i)
{
	int		stat_loc;
	int		exit_status;
	int 	j;
	
	signal(SIGINT, sigint_child_handler);//new
	signal(SIGQUIT, SIG_IGN);//new
	close(p->pipes[i][1]);
	p->prev_pipe = p->pipes[i][0];
	if (i == p->nr_cmds  - 1)
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
			close (p->pipes[j][0]);
	}
	(void)cmd;
}

/*Execution of multiple commands using forks*/
bool	execute_commands(t_shell *p, t_lst *cmd, int i)
{
	t_lst	*current;

	current = cmd;
	allocate_pipe_memory(p);
	while (i < p->nr_cmds)
	{
		infile(current); // to be corrected
		if (current->run == true)
			outfile(current);
		if (current->run == true)
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
		i++;
	}
	i = 0;
	while (i++ < p->nr_cmds -1)
		wait(NULL);
	free_allocation_malloc_pipes(p);
	return (true);
}

void	execute(t_shell *p)
{
	t_lst	*current;

	current = p->token_list;
	// while (current != NULL)
	// {
		p->nr_cmds = count_cmd(current);
		if (p->nr_cmds == 1 && is_build_in_cmd(current) == true) //change is_built_in
			p->command_status = handle_build_in(p, current);	
		else
			execute_commands(p, current, 0);
		
	// 	current = current->next;
	// }
	signal(SIGINT, handle_sigint);
}
