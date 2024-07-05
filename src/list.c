/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:26:30 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/05 19:59:37 by mtocu            ###   ########.fr       */
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

int	count_cmd(t_lst	*nodes)
{
	t_lst	*current;
	int		count;

	current = nodes;
	count = 0;
	while (current != NULL)
	{
		if (current->type == CMD)
			count++;
		else if (current->token == PIPE)
			current->remove = true;
		current = current->next;
	}
	return (count);
}

void	print_list(t_lst *nodes)
{
	t_lst	*current;
	int		i;

	current = nodes;
	while (current != NULL)
	{
		if (current->token == WORD || current->token == SQUOTE
			|| current->token == DQUOTE)
		{
			printf("token content word type: %s\n", current->content);
			printf("token type: %u\n", current->token);
			printf("Operator type: %i\n", current->type);
		}
		else
		{
			printf("token type : %i\n", current->token);
			printf("Operator type: %i\n", current->type);
		}
		i = -1;
		if (current->args != NULL)
			while (current->args[++i] != NULL)
				printf("   args: %s\n", current->args[i]);
		current = current->next;
	}
}

void	print_files(t_file *file)
{
	t_file	*current;

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
	int		i;

	current = nodes;
	while (current != NULL)
	{
		if (current->type == CMD)
		{
			printf("CMD = %s\n", current->content);
			i = -1;
			if (current->args != NULL)
				while (current->args[++i] != NULL)
					printf("   args: %s\n", current->args[i]);
			if (current->infile != NULL)
				print_files(current->infile);
			if (current->outfile != NULL)
				print_files(current->outfile);
		}
		else if (current->token == PIPE)
			printf("current token %d\n", current->token);
		current = current->next;
	}
}

void	print_env(t_env_list *nodes)
{
	t_env_list	*current;

	current = nodes;
	while (current != NULL)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
