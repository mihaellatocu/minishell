/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:55:29 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/14 14:25:13 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*a;

	if (s == NULL)
		return (NULL);
	a = s;
	while (n)
	{
		*a = c;
		a++;
		n--;
	}
	return (s);
}
/*
int	main(void)
{
	char cuvant[] = "Mihaela cuvant";
	printf("Before: %p\n", &cuvant);
	memset(cuvant, 'p', 2);
	char word[] = "astronaut";

	printf("after pt cuvant: %p\n", cuvant);
	printf("Before: %s\n", word );

	ft_memset(word, 'd', 4);


	printf("after: %s\n", word);
	//printf("%u\n", number);
}*/
