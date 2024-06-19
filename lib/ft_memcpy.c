/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:55:44 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/14 14:42:38 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destination;
	const unsigned char	*source;

	destination = dest;
	source = src;
	if (destination != NULL && source != NULL)
	{
		while (n > 0)
		{
			*(destination++) = *(source++);
			n--;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char dest[] = "aaaaaaaaaaaaaa";
	const char *source = "stuvxyz";
	printf("%p %p\n", dest, source); //stuv
		
	 ft_memcpy(dest, source, 4);
	 printf("%s\n", dest);
}*/
