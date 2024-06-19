/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:57:48 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/04 19:47:24 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*position;

	i = 0;
	position = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			position = &s[i];
		i++;
	}
	if (s[i] == (char)c)
		position = &s[i];
	return ((char *)position);
}
/*
int	main(void)
{
	char s[] = "telenovela";
	int c = 0;
	printf("Before function: %s %p\n", s, s);
	printf("after: %s %p\n", strrchr(s, c), strrchr(s, c));
	printf("after: %s %p \n", ft_strrchr(s, c), ft_strrchr(s,c));
	return (0);
}*/
