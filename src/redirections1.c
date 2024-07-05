/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:24:28 by mtocu             #+#    #+#             */
/*   Updated: 2024/06/21 13:44:48 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redirection(t_lst *cmd, t_lst *node, int type)
{
	if (type == INFILE)
		file_lstadd_back(&cmd->infile,  file_lstnew(node->token, node->next->content, 0));
	else
		file_lstadd_back(&cmd->outfile, file_lstnew(node->token, node->next->content, 1));
	// printf("node content for file %s\n", node->content);
	node->next->remove = true;
	node->remove = true;
}

/*Once a redirection is found, this function search for the closer command
	to assign the redirection*/
t_lst	*find_closer_command(t_lst *command) 
{
	t_lst *current;

	current = command;
	while(current->next != NULL)
	{
		current = current->next;
		if (current->type == CMD || current->token == PIPE)
			break;
	}
	if (current->type == CMD)
		return (current);
	current = command;
	while(current->prev != NULL)
	{
		current = current->prev;
		if (current->type == CMD || current->token == PIPE)
			break;
	}
	if (current->type == CMD)
		return (current);
	return (NULL);
}

int	assign_redirection(t_lst *node, t_lst *command) 
{
	t_lst	*cmd;

	cmd = command;
	if (node->next != NULL && (node->next->token == WORD)) // to be added Dquote and Squote
	{
		if(is_infile_redirection(node)) // < file
		{
			// if( is_infile_redirection(node->next && node->next.is_not_valid_cmd))
			// 	return (2); - to be handled later
			handle_redirection(cmd, node, INFILE);
		}
		else if(is_outfile_redirection(node)) // > file
		{
			// if(node->next && node->next.is_not_valid_cmd)
			// 	return(2);
			handle_redirection(cmd, node, OUTFILE);
		}
		return (0);
	}
	return (2);
}	

void	find_redirections(t_lst *node)
{
	t_lst	*current;
	t_lst	*command;

	current = node;
	while(current != NULL)
	{
		if (is_infile_redirection(current) || is_outfile_redirection(current)) // (< and << ) or ( > and >>)
		{
			command = find_closer_command(current);
			assign_redirection(current, command);

		}
		current = current->next;
	}

	
}
