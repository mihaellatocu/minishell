/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:01:45 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/05 19:57:43 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return current working directory*/
int	handle_pwd_cmd(t_shell *p, t_lst *cmd)
{
	char	dir[1024];
	int		original_stdout;

	(void)p;
	if (getcwd(dir, 1024))
	{
		original_stdout = open_fd_solo_cmd(p, cmd);
		if (original_stdout == -2)
			return (1);
		printf("%s\n", dir);
		dup2(original_stdout, STDOUT_FILENO);
	}
	else
		return (write(2, "minishell: pwd: error reading directory\n", 41), 1);
	return (0);
}
