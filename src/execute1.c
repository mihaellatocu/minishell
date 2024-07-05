/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:18:55 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/04 14:49:35 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	execute_cmd(t_lst *node, t_env_list *env)
// {
// 	t_lst *current;
	

	
// }

void	execute(t_shell *p)
{
	t_lst	*current;
	int		count_cmds;

	current = p->token_list;
	count_cmds = 0;
	while (current != NULL)
	{
		if(current->type == CMD)
		{
			count_cmds = count_cmd(current);
			if (count_cmds == 1 && is_only_one_cmd(current) == true)
				p->command_status = handle_build_in(p, current);
			
			// open_infile();
			// open_outfile();
		}
		current = current->next;
	}

}