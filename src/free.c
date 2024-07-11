/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:19:41 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 13:48:48 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// free arr or arguments
void	free_arg_contents(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	unlink(".here_doc");
}

static void	free_files(t_file *file)
{
	t_file	*temp;
	t_file	*current;

	current = file;
	while (current != NULL)
	{
		free(current->name);
		temp = current->next;
		free (current);
		current = temp;
	}
}

// free all nodes of tokens
void	free_allocation_malloc(t_lst **nodes, char *line)
{
	t_lst	*current;
	t_lst	*tmp;

	current = *nodes;
	while (current != NULL)
	{
		if (current->type == CMD)
		{
			free(current->content);
			if (current->args != NULL)
				free_arg_contents(current->args);
			free_files(current->infile);
			free_files(current->outfile);
		}
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*nodes = NULL;
	if (line != NULL)
		free(line);
}

// free env list
void	free_allocation_malloc_env(t_env_list **nodes)
{
	t_env_list	*current;
	t_env_list	*tmp;

	current = *nodes;
	if (current != NULL)
	{
		while (current != NULL)
		{
			if (current->key != NULL)
				free(current->key);
			if (current->value)
				free(current->value);
			tmp = current->next;
			free(current);
			current = tmp;
		}
	}
	*nodes = NULL;
}

// free arg nodes or any unwanted nodes
void	cleaning_args(t_lst **nodes)
{
	t_lst	*current;
	t_lst	*tmp;

	current = *nodes;
	while (current != NULL)
	{
		tmp = current->next;
		if (current->remove == true)
		{
			if (current->prev != NULL)
				current->prev->next = tmp;
			else
				*nodes = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			if (current->content != NULL)
				free(current->content);
			free(current);
		}
		current = tmp;
	}
}

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
