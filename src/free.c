/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:19:41 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/04 15:02:04 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	free_arg_contents(char **args) // free arr or arguments
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		//printf("argument deleted:     %s\n", args[i]);
		free(args[i]);
		i++;
	}
	free(args);
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

void	free_allocation_malloc(t_lst **nodes, char *line) // free all nodes of tokens
{
	t_lst *current;
	t_lst *tmp;

	current = *nodes;
	while(current != NULL)
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
	if(line != NULL)
		free(line);
}

void	free_allocation_malloc_env(t_env_list **nodes) // free env list
{
	t_env_list	*current;
	t_env_list	*tmp;

	current = *nodes;
	if (current != NULL)
	{
		while(current != NULL)
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

void	cleaning_args(t_lst **nodes)// free arg nodes or any unwanted nodes
{
	t_lst *current;
	t_lst *tmp;

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
