/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1_find_path_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 16:21:31 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-15 16:21:31 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_in_env(t_env_list *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			return (ft_strdup(env->value));
			break ;
		}
		env = env->next;
	}
	return (NULL);
}

static void	pipe_error(void)
{
	perror("Pipe creation failed");
	exit(EXIT_FAILURE);
}

void	free_env_vars_from_child(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	return ;
}

void	allocate_pipe_memory(t_shell *p)
{
	int	i;

	i = 0;
	p->pipes = (int **)malloc(p->nr_cmds * sizeof(int *));
	p->pid = (pid_t *)malloc(p->nr_cmds * sizeof(pid_t));
	if (!p->pipes || !p->pid)
		ft_malloc_error();
	while (i < p->nr_cmds)
	{
		p->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!p->pipes[i])
			ft_malloc_error();
		if (pipe(p->pipes[i]) == -1)
			pipe_error();
		i++;
	}
}
