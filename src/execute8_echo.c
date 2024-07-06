/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute8_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:35:01 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/06 16:03:17 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_echo_cmd(t_shell *p, t_lst *cmd)
{
	int	i;

	(void)p;
	i = 1;
	if (!cmd->args[i])
		return (printf("\n"), 0);
	else
	{
		if (ft_strncmp(cmd->args[i], "-n", 3) == 0)
			i++;
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			i++;
			if (cmd->args[i])
				printf(" ");
		}
	}
	if (ft_strncmp(cmd->args[1], "-n", 3) != 0)
		printf("\n");
	return (0);
}
