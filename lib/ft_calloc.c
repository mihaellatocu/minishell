/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:09:00 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/10 18:38:38 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if ((count >= 4294967296 || size >= 4294967296) && count && size)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
/*
int	main(void)
{
	printf("%d\n", ft_memcmp(ft_calloc(10, 4), calloc(10, 4), 40));
//	printf("%d\n", calloc(10, 4));
}*/
