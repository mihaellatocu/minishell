/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:18:55 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 14:41:01 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exit(error_execve(cmd->args[0]));
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

	if (p->error == false)
	{
		current = p->token_list;
		p->nr_cmds = count_cmd(current);
		if (p->nr_cmds == 1 && is_build_in_cmd(current) == true)
			p->command_status = handle_build_in(p, current);
		else
			execute_commands(p, current, -1);
		signal(SIGINT, handle_sigint);
	}
}
