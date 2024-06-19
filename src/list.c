/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:26:30 by mtocu             #+#    #+#             */
/*   Updated: 2024/06/19 15:40:37 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*Creating the list of tokens*/
t_lst	*lstnew(char *content, t_token token)
{
	t_lst	*result;

	result = (t_lst *)malloc(sizeof(t_lst));
	if (!result)
		return (NULL);
	result->content = content;
	result->token = token;
	result->next = NULL;
	result->prev = NULL;
	result->args = NULL;
	result->infile = NULL;
	result->outfile = NULL;
	result->remove = false;
	return (result);
}

void	lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*current;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

void	print_list(t_lst *nodes)
{
	t_lst	*current;

	current = nodes;
	printf("--------------------------------------------\n");
	while (current != NULL)
	{
		if (current->token == WORD)
		{
			printf("token content word type: %s\n", current->content);
			printf("token  type: %u\n", current->token);
			printf("Operator type: %i\n", current->type);
		}
		else
		{
			printf("token type : %i\n", current->token);
			printf("Operator type: %i\n", current->type);
		}
		int i = -1;
		if (current->args != NULL)
			while (current->args[++i] != NULL)
				printf("   args: %s\n", current->args[i]);
		printf("--------------------------------------------\n");
		current = current->next;
	}
	
}

void	print_files(t_file *file)
{
	t_file *current;

	current = file;
	while (current != NULL)
	{
		printf("   infile or outfile: %s\n", current->name);
		printf("   infile or outfile type: %u\n", current->token);
		current = current->next;
	}
}

void	print_list_cmd(t_lst *nodes)
{
	t_lst	*current;

	current = nodes;
	printf("--------------------------------------------\n");
	while (current != NULL)
	{
		if (current->type == CMD)
		{
			printf("CMD = %s\n", current->content);
			int i = -1;
			if (current->args != NULL)
				while (current->args[++i] != NULL)
					printf("   args: %s\n", current->args[i]);
			if (current->infile != NULL)
				print_files(current->infile);
			if (current->outfile != NULL)
				print_files(current->outfile);
		}
		current = current->next;
	}
}
void	print_env(t_env_list *nodes)
{
	t_env_list	*current;
	
	current = nodes;
	while(current != NULL)
	{
		if (current->value != NULL)
			printf("Env:  %s\n", current->value);
		
		current = current->next;
	}
	//printf("Home env: %s\n", getenv("PATH"));
}

