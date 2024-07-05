/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:01:45 by mtocu             #+#    #+#             */
/*   Updated: 2024/06/28 15:11:49 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*return current working directory*/
int	handle_pwd_cmd(t_shell *p, t_lst *cmd)
{
	char	dir[1024];
	
	(void)p;
	(void)cmd;
	if(getcwd(dir, 1024))
	{
		printf("%s\n", dir);
	}
	else
		return (write(2, "minishell: pwd: error reading directory\n", 41), 1);
	return (0);
}
