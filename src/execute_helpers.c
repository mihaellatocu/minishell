/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 14:24:23 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-15 14:24:23 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//remove duplicate env from export function
void	delete_env_dups(t_env_list **nodes)
{
	t_env_list	*current;
	t_env_list	*tmp;

	current = *nodes;
	while (current != NULL)
	{
		tmp = current->next;
		if (current->to_remove == true)
		{
			if (current->prev != NULL)
				current->prev->next = tmp;
			else
				*nodes = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			if (current->value != NULL)
				free(current->value);
			if (current->key != NULL)
				free(current->key);
			free(current);
		}
		current = tmp;
	}
}

void	find_duplicate_env(t_env_list *head_env_list)
{
	size_t		len_current;
	size_t		len_temp;
	t_env_list	*temp;
	t_env_list	*current;

	current = head_env_list;
	while (current != NULL)
	{
		len_current = ft_strlen(current->key);
		temp = current;
		while (temp != NULL)
		{
			len_temp = ft_strlen(temp->key);
			if ((temp != current) && (len_current == len_temp) && \
				strncmp(current->key, temp->key, len_current) == 0)
				current->to_remove = true;
			temp = temp->next;
		}
		current = current->next;
	}
}
