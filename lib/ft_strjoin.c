/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:25:44 by mtocu             #+#    #+#             */
/*   Updated: 2024/03/21 19:18:05 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned char	*new_str;
	size_t			j;
	size_t			i;

	j = 0;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	new_str = malloc(sizeof(char) * ((int)ft_strlen(s1) + \
				(int)ft_strlen(s2)) + 1);
	while (s1 && (int)i < (int)ft_strlen(s1))
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2 && (int)j < (int)ft_strlen(s2))
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return ((char *)new_str);
}
/*
int	main(void)
{
	char *a = "abc";
	char *b = "";
	printf("%s\n", ft_strjoin(a, b));
}*/
