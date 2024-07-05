/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute5_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:34:03 by mtocu             #+#    #+#             */
/*   Updated: 2024/06/28 15:16:33 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strisnum(char *str)
{
	int		i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\"' || str[i] == '\'')
	{
		in_quotes = true;//opening quotes
		i++;
	}
	while (str[i])
	{
		if (in_quotes && (str[i] == '\"' || str[i] == '\''))
			in_quotes = false;//closing quotes
		else if (!in_quotes && (str[i] == '\"' || str[i] == '\''))
			return (false); // if quotes are in the middle without opening
		else if (!ft_isdigit((char)str[i])) // non numeric charcater found
			return (false);
		i++;
	}
	return (!in_quotes); // returning 1 for true and 0 for false
}

int	handle_exit_cmd(t_shell *p, t_lst *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
		return (write(2, "exit\nexit: too many arguments\n", 30), 1);
	else if (cmd->args[1] != NULL && !ft_strisnum(cmd->args[1]))
	{
		p->run = false;
		return(write(2, "exit\nexit: numeric argument required\n", 37), 2);
	}
	else if (cmd->args[1])
		exit_status = ft_atoi(cmd->args[1]);
	p->run = false;
	printf("exit\n");
	return (exit_status);
}