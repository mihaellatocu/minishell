/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:23:34 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/03 15:18:55 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*env_lstnew(char *value, char *key)
{
	t_env_list	*env_lst;

	env_lst = (t_env_list *)malloc(sizeof(t_env_list));
	if (!env_lst)
		return (NULL);
	env_lst->key = ft_strdup(key);
	env_lst->value = ft_strdup(value);
	env_lst->next = NULL;
	env_lst->prev = NULL;
	env_lst->to_remove = false;
	return (env_lst);
}

void	env_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*ptr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
}

static void	init_env(t_shell *p, char **envp)
{
	int		i;
	char	*value;
	char	*key;
	char	**env;
	int		j;

	i = 0;
	while(envp[i] != NULL)
	{
		j = -1;
		env = ft_split(envp[i], '='); //HOME=/home/user 
		key = env[0]; //HOME
		value = getenv(key);
		if(value)
			env_lstadd_back(&p->envir, env_lstnew(value, key));
		else
			env_lstadd_back(&p->envir, env_lstnew("", key));
		while (env[++j] != NULL)
			free(env[j]);
		free(env);
		i++;
	}
	return ;
}

void init(t_shell *p, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	p->token_list = NULL;
	p->error = false; // for export cmd
	p->envir = NULL;
	p->run = true;
	p->command_status = 0;
	
	if(envp)
		init_env(p, envp);
}
