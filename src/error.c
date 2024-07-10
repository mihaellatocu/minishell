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

int	error_execve(char *str)
{
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
	//free_all_memory(s);
	return (err_no);
}