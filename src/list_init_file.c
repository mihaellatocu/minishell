/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:23:45 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/06 11:23:53 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Functions that manage the list of infiles and outfiles*/
t_file	*file_lstnew(t_token token, char *name, int fd)
{
	t_file	*file_list;

	(void)fd;
	file_list = (t_file *)malloc(sizeof(t_file));
	if (!file_list)
		return (NULL);
	file_list->name = ft_strdup(name);
	file_list->next = NULL;
	file_list->prev = NULL;
	file_list->token = token;
	return (file_list);
}

void	file_lstadd_back(t_file **list_of_files, t_file *new_file)
{
	t_file	*ptr;

	if (!new_file)
		return ;
	if (!*list_of_files)
	{
		*list_of_files = new_file;
		return ;
	}
	ptr = *list_of_files;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_file;
	new_file->prev = ptr;
}

int	file_lstsize(t_file *list)
{
	int		count;
	t_file	*current;

	count = 0;
	current = list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
