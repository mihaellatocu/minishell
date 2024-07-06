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
