/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:33:21 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 14:02:21 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Print error in case malloc() fails*/
void	ft_malloc_error(void)
{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
}

/*Print error in case fork() fails*/
void	ft_fork_error(void)
{
	perror("Fork failed");
	exit(EXIT_FAILURE);
}

int	error_execve(char *str, t_shell *p)
{(void)p;
	int	err_no;
	DIR	*dir;

	write(2, str, ft_strlen(str));
	dir = opendir(str);
	if (dir != NULL)
	{
		err_no = 126;
		write(2, ": Is a directory\n", 18);
	}
	else
	{
		err_no = 127;
		if (str[0] == '.' || str[0] == '/')
			write(2, ": No such file or directory\n", 29);
		else
			write(2, ": command not found\n", 20);
	}
	return (err_no);
}

/*Print an error in case redirection is missing from command*/
void	redirection_error(t_lst *current)
{
	if (current->next == NULL)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putchar_fd(current->next->token, 2);
		ft_putstr_fd("'\n", 2);
	}
}
