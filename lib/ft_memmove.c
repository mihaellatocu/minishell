/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:31:24 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/06 17:59:47 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*destination;
	unsigned const char	*source;

	i = 0;
	destination = dest;
	source = src;
	if (destination == NULL || source == NULL)
		return (NULL);
	if (source < destination)
	{
		while (++i <= n)
			destination[n - i] = source[n - i];
	}
	else
	{
		while (n-- > 0)
			*(destination++) = *(source++);
	}
	return (dest);
}
/*
int	main(void)
{
	char dest[40];
	const char *src= "abcdef";
	printf("%p %p\n", &dest, &src);
	memmove(dest, src, 4);
	printf("%s %s\n", dest, src);
	ft_memmove(dest, src, 40);
	printf("%s %s\n", dest, src);
}*/
