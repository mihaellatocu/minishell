/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute7_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:33:24 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/05 19:44:21 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_for_export(t_env_list *nodes)
{
	t_env_list	*current;

	current = nodes;
	while (current != NULL)
	{
		printf("declare -x %s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}

bool	find_equal(char *str, int *pos)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			*pos = i;
			return (true);
		}
		i++;
	}
	return (false);
}

void	free_temporary_vars(char **key, char **variable)
{
	free(*key);
	free(*variable);
	*key = NULL;
	*variable = NULL;
}

//find key and value 
int	find_key_value(char *arg, char **key, char **value, int pos_equal)
{
	int		start;

	start = pos_equal -1;
	while (start > 0 && (ft_isalnum(arg[start]) || arg[start] == '_'))
		start--;
	if (start != 0)
	{
		*key = NULL;
		*value = NULL;
		return (1);
	}
	else
	{
		*key = malloc(sizeof(char) * (pos_equal + 1));
		ft_strlcpy(*key, arg, pos_equal + 1);
		if (ft_strlen(arg) - pos_equal > 1)
		{
			*value = malloc(sizeof(char) * (ft_strlen(arg) - pos_equal));
			ft_strlcpy(*value, arg + (pos_equal + 1), ft_strlen(arg + 1));
		}
		else
			*value = ft_strdup("");
		return (0);
	}
}

t_env_list	*find_export_var(t_lst *cmd, t_shell *p, char *key, char *value)
{
	t_env_list	*current;
	int			i;
	int			pos;

	i = 0;
	current = p->envir;
	while (cmd->args[++i] != NULL)
	{
		pos = -1;
		if (!(ft_isalpha(cmd->args[i][0]) || cmd->args[i][0] == '_'))
		{
			p->error = true;
			p->command_status = 1;
		}
		else if (find_equal(cmd->args[i], &pos))
		{
			p->command_status = find_key_value(cmd->args[i], &key, &value, pos);
			if (key != NULL)
			{
				env_lstadd_back(&current, env_lstnew(value, key));
				free_temporary_vars(&key, &value);
			}
		}
	}
	return (current);
}

int	handle_export_cmd(t_shell *p, t_lst *cmd)
{
	t_env_list	*current;

	(void)*cmd;
	current = p->envir;
	if (!cmd->args[1])
		print_env_for_export(current);
	else
	{
		p->envir = find_export_var(cmd, p, NULL, NULL);
		if (p->error || p->command_status == 1)
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
	}
	p->error = false;
	return (p->command_status);
}
