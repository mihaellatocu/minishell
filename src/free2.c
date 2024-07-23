/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 12:37:58 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-15 12:37:58 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Free alloc malloc pipes*/
void	free_allocation_malloc_pipes(t_shell *p)
{
	int	i;

	i = 0;
	while (i < p->nr_cmds)
	{
		free(p->pipes[i]);
		i++;
	}
	free(p->pipes);
	p->pipes = NULL;
	free(p->pid);
	p->pid = NULL;
}

/*This function calls all functions to free memory allocated*/
void	free_all_memory(t_shell *p)
{
	free_allocation_malloc(&p->token_list, p->line);
	p->token_list = NULL;
	p->line = NULL;
	free_allocation_malloc_pipes(p);
	free_allocation_malloc_env(&p->envir);
	p->envir = NULL;
}

//removing key and value after finding the valid key and adding on the env list
void	free_temporary_vars(char **key, char **variable)
{
	free(*key);
	free(*variable);
	*key = NULL;
	*variable = NULL;
}
