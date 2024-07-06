/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:17:54 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/05 19:19:45 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_char2(char **tofree)
{
	size_t	i;

	i = 0;
	if (!tofree)
		return ;
	while (tofree[i])
		free(tofree[i++]);
	free(tofree);
}

void	ft_free_char3(char ***tofree)
{
	size_t	i;

	i = 0;
	if (!tofree)
		return ;
	while (tofree[i])
		ft_free_char2(tofree[i++]);
	free(tofree);
}
