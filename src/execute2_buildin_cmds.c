/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:29:59 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/06 15:21:50 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This Function open all the infile and outile for the command*/
void	open_fd(t_lst *cmd, t_shell *p)
{
	if (infile(cmd) == 0)
	{
		if (outfile(cmd) == -1)
		{
			p->command_status = 1;
			cmd->run = false;
		}
	}
	else
	{
		p->command_status = 1;
		cmd->run = false;
	}
}

int	open_fd_solo_cmd(t_shell *p, t_lst *cmd)
{
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	if (p->nr_cmds == 1)
	{
		open_fd(cmd, p);
		if (cmd->run == false)
			return (-2);
		if (cmd->fd_out != STDOUT_FILENO)
			dup2(cmd->fd_out, STDOUT_FILENO);
	}
	return (original_stdout);
}

/*Check if it's only one command and if that command is built in*/
bool	is_build_in_cmd(t_lst *node)
{
	bool	is_build_in;

	is_build_in = false;
	if (ft_strncmp(node->args[0], "cd", 3) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "pwd", 4) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "env", 4) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "export", 7) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "unset", 6) == 0)
		is_build_in = true;
	if (ft_strncmp (node->args[0], "echo", 5) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "exit", 5) == 0)
		is_build_in = true;
	return (is_build_in);
}

int	handle_build_in(t_shell *p, t_lst *command)
{
	if (ft_strncmp(command->args[0], "cd", 3) == 0)
		return (handle_cd_cmd(p, command));
	if (ft_strncmp(command->args[0], "pwd", 4) == 0)
		return (handle_pwd_cmd(p, command));
	if (ft_strncmp(command->args[0], "exit", 5) == 0)
		return (handle_exit_cmd(p, command));
	if (ft_strncmp(command->args[0], "env", 4) == 0)
		return (handle_env_cmd(p, command));
	if (ft_strncmp(command->args[0], "unset", 6) == 0)
		return (handle_unset_cmd(p, command));
	if (ft_strncmp(command->args[0], "export", 7) == 0)
		return (handle_export_cmd(p, command));
	if (ft_strncmp(command->args[0], "echo", 5) == 0)
		return (handle_echo_cmd(p, command));
	return (-1);
}
