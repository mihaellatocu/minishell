/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1_find_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 16:07:24 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-15 16:07:24 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
