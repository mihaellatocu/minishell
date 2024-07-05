/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:23:09 by mtocu             #+#    #+#             */
/*   Updated: 2024/06/15 17:23:13 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//not used yet
t_command *create_command(char **args) 
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;
    cmd->args = args;
    cmd->next = NULL;
    return cmd;
}

void add_command(t_shell *shell, char **args) 
{
    t_command *cmd = create_command(args);
    if (!cmd) return;

    if (!shell->cmd) {
        shell->cmd = cmd;
    } else {
        t_command *current = shell->cmd;
        while (current->next) {
            current = current->next;
        }
        current->next = cmd;
    }
}

void free_cmd(t_shell *shell) 
{
    t_command *current = shell->cmd;
    while (current) {
        t_command *next = current->next;
        free(current->args);
        free(current);
        current = next;
    }
}
