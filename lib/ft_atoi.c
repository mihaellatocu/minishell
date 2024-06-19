/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:11:52 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/09 14:59:03 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		nr;

	i = 0;
	nr = 0;
	sign = 1;
	while (!ft_isprint(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		++i;
	while (str[i] && ft_isdigit(str[i]))
	{
		nr = nr * 10 + (str[i] - '0');
		i++;
	}
	return (nr * sign);
}
/*
int	main(void)
{
	const char *s = "a1";
	printf("%d\n", ft_atoi(s));
}*/
