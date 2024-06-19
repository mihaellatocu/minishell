/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:00:27 by mtocu             #+#    #+#             */
/*   Updated: 2024/03/21 19:17:23 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s1, char *s2, int n)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	if (s2 == NULL || ft_strlen(s2) == 0)
		return ((char *)s1);
	if (ft_strlen(s2) > n)
		return (NULL);
	while (i + ft_strlen(s2) <= n && s1[i])
	{
		flag = 1;
		j = 0;
		while (j < ft_strlen(s2) && s2[j])
		{
			if (s1[i + j] != s2[j])
				flag = 0;
			++j;
		}
		if (flag == 1)
			return ((char *)&s1[i]);
		++i;
	}
	return (NULL);
}
/*
int	main(void)
{
	char *s1 = "aaabcabcad";
	char *s2 = "c";
	//char *ptr;
	//ptr = ft_strnstr(s1, s2, 3);
	//printf("%d\n", strnstr(s1, s2, 10));
	printf("%s\n", ft_strnstr(s1, s2, 10));
	//char	*str;
//	ABCDg
//	ABCDE
}*/
