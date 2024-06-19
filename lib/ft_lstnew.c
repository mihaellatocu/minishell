/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:26:30 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/13 15:27:01 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include <stdlib.h>
//#include <stdio.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	result = (t_list *)malloc(sizeof(t_list));
	if (!result)
		return (NULL);
	result->content = (void *)content;
	result->next = NULL;
	return (result);
}
/*
int	main(void)
{
	t_list *head;
	t_list *tmp;

	tmp = ft_lstnew(32);
	head = tmp;
	tmp = ft_lstnew(8);
	tmp->next = head;
	head = tmp;

	tmp = ft_lstnew(34);
	tmp->next = head;
	head = tmp;


	ft_lstnew(head);

}*/
