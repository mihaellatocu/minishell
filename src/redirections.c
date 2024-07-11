/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:24:34 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/05 19:30:06 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Return TRUE if redirection is < or <<*/
static bool	is_in_redirection(t_lst *prev)
{
	if (prev->token == DLESS || prev->token == LESS)
		return (true);
	return (false);
}

/*return TRUE if redirection is > or >> */
static bool	is_out_redirection(t_lst *prev)
{
	if (prev->token == GREAT || prev->token == DGREAT)
		return (true);
	return (false);
}

/*Check if the token is an operator*/
static bool	is_operator(t_lst *current)
{
	if (current->token == DLESS || current->token == LESS
		|| current->token == DGREAT || current->token == GREAT
		|| current->token == PIPE)
		return (true);
	return (false);
}

bool	is_infile_redirection(t_lst *current)
{
	if (current->token == DLESS || current->token == LESS)
		return (true);
	return (false);
}

bool	is_outfile_redirection(t_lst *current)
{
	if (current->token == GREAT || current->token == DGREAT)
		return (true);
	return (false);
}

/*Cheching if a token is a command, an argument or an operator*/
void	set_command_structure(t_lst *node, bool found_cmd)
{
	t_lst	*current;

	current = node;
	while (current != NULL)
	{
		if (is_operator(current))
			current->type = OPERATOR;
		else if (current->prev != NULL && is_in_redirection(current->prev))
			current->type = INFILE;
		else if (current->prev != NULL && is_out_redirection(current->prev))
			current->type = OUTFILE;
		else if (found_cmd == true)
			current->type = ARG;
		else
		{
			current->type = CMD;
			found_cmd = true;
		}
		if (current->token == PIPE)
			found_cmd = false;
		current = current->next;
	}
}
