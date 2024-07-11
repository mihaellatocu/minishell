/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:24:28 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 13:42:21 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redirection(t_lst *cmd, t_lst *node, int type)
{
	if (type == INFILE)
		file_lstadd_back(&cmd->infile, file_lstnew(node->token, \
			node->next->content, 0));
	else
		file_lstadd_back(&cmd->outfile, file_lstnew(node->token, \
			node->next->content, 1));
	node->next->remove = true;
	node->remove = true;
}

/*Once a redirection is found, this function search for the closer command
	to assign the redirection*/
t_lst	*find_closer_command(t_lst *command)
{
	t_lst	*current;

	current = command;
	while (current->next != NULL)
	{
		current = current->next;
		if (current->type == CMD || current->token == PIPE)
			break ;
	}
	if (current->type == CMD)
		return (current);
	current = command;
	while (current->prev != NULL)
	{
		current = current->prev;
		if (current->type == CMD || current->token == PIPE)
			break ;
	}
	if (current->type == CMD)
		return (current);
	return (NULL);
}

static bool	is_word(t_token token)
{
	if (token == WORD)
		return (true);
	if (token == SQUOTE)
		return (true);
	if (token == DQUOTE)
		return (true);
	return (false);
}

int	assign_redirection(t_lst *node, t_lst *command)
{
	t_lst	*cmd;

	cmd = command;
	if (node->next != NULL && is_word(node->next->token))
	{
		if (is_infile_redirection(node))
		{
			handle_redirection(cmd, node, INFILE);
		}
		else if (is_outfile_redirection(node))
		{
			handle_redirection(cmd, node, OUTFILE);
		}
		return (0);
	}
	return (2);
}

// (< and << ) or ( > and >>)
void	find_redirections(t_lst *node, t_shell *p)
{
	t_lst	*current;
	t_lst	*command;
	int		error;

	current = node;
	while (current != NULL)
	{
		if (is_infile_redirection(current) || is_outfile_redirection(current))
		{
			command = find_closer_command(current);
			error = assign_redirection(current, command);
			if (error == 2)
			{
				p->command_status = error;
				redirection_error(current);
				p->error = true;
				break ;
			}
		}
		current = current->next;
	}
}
