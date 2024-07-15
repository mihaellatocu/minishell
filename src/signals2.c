/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 12:37:23 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-15 12:37:23 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handle ctrl-D (EOF) to exit the shell */
void	handle_eof(void)
{
	printf("exit\n");
	exit(0);
}