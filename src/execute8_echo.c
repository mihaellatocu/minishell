/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute8_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:35:01 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/23 15:15:02 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	should_wr(t_lst *cmd, char c, char *str, int i)
{
	(void)cmd;
	if (c == '$' && str[i + 1] != '\0')
		return (false);
	return (true);
}

// Function to write a string to the output
static void	write_str(t_lst *cmd, char *str, int i, int cur)
{
	bool	in_double_quotes;
	bool	in_single_quotes;
	char	c;

	in_double_quotes = false;
	in_single_quotes = false;
	while (str[i])
	{
		c = str[i];
		if (c == '\"' && !in_single_quotes && cur == 1)
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue ;
		}
		if (c == '\'' && !in_double_quotes && cur == 1)
		{
			in_single_quotes = !in_single_quotes;
			i++;
			continue ;
		}
		if (should_wr(cmd, c, str, i) || in_double_quotes || in_single_quotes)
			write(1, &c, 1);
		i++;
	}
}

int	handle_echo_cmd(t_shell *p, t_lst *cmd)
{
	int		i;
	int		original_stdout;

	i = 1;
	original_stdout = open_fd_solo_cmd(p, cmd);
	if (original_stdout == -2)
		return (dup2(original_stdout, STDOUT_FILENO), 1);
	if (!cmd->args[i])
		return (printf("\n"), 0);
	else if (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "-n", 3) == 0)
			i++;
		while (cmd->args[i])
		{
			write_str(cmd, cmd->args[i], 0, i);
			i++;
			if (cmd->args[i])
				write (1, " ", 1);
		}
	}
	if (ft_strncmp(cmd->args[1], "-n", 3) != 0)
		write(1, "\n", 1);
	dup2(original_stdout, STDOUT_FILENO);
	return (1);
}
