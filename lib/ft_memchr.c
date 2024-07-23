/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:53:48 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 14:37:59 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*string;

	i = 0;
	string = (const unsigned char *)s;
	while (i < n)
	{
		if (string[i] == (unsigned char)c)
			return ((void *)(string + i));
		++i;
	}
	return (NULL);
}
/*
int	main(void)
{
	char *s = "abracadabra";
	char *str = ft_memchr(s, 'r', 10);
	printf("%p\n", &str);
}*/
