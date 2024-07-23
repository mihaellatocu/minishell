/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute6_env_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:32:28 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/05 16:33:19 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_env_cmd(t_shell *p, t_lst *cmd)
{
	(void)cmd;
	if (p->token_list->args[1] == NULL)
	{
		print_env(p->envir);
	}
	return (0);
}

int	handle_unset_cmd(t_shell *p, t_lst *cmd)
{
	t_env_list	*current;
	int			original_stdout;

	current = p->envir;
	original_stdout = open_fd_solo_cmd(p, cmd);
	dup2(original_stdout, STDOUT_FILENO);
	while (current != NULL)
	{
		if (cmd->args[1] && ft_strncmp(current->key, cmd->args[1],
				ft_strlen(cmd->args[1]) + 1) == 0)
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next && current->prev)
				current->next->prev = current->prev;
			if (current == p->envir)
				p->envir = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		current = current->next;
	}
	return (0);
}
