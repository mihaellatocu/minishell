/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:01:55 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/04 14:50:15 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Check if HOME variable is set in env list*/
char	*find_home_env(t_shell *p)
{
	t_env_list *current;

	current = p->envir;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		if(ft_strncmp(current->key, "HOME", 5) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	count_args(char	**args_from_a_node)
{
	int	i;

	i = 0;
	while(args_from_a_node[i] != NULL)
		i++;
	return (i);
}

int	handle_cd_cmd(t_shell *p, t_lst *cmd)
{
	char	*home;
	char 	*dir;
	int		num_args;

	dir = cmd->args[1];
	num_args = count_args(cmd->args);
	if (num_args > 2)
		return (write(2, "cd: too many arguments\n", 24), 1); // 1 for failling cmd
	if (num_args == 1)
	{
		home = find_home_env(p);
		if (home == NULL)
			return(write(2, "cd: HOME not set\n", 18), 1);
		else
			return(chdir(home), 0);
	}
	else if (chdir(dir) != 0)
		return (write(2, "cd: No such file of directory\n", 31), 1);
	return (0);
}