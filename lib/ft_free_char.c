#include "libft.h"

void	ft_free_char2(char **tofree)
{
	size_t	i;

	i = 0;
	if(!tofree)
		return ;
	while(tofree[i])
		free(tofree[i++]);
	free(tofree);
}

void	ft_free_char3(char ***tofree)
{
	size_t	i;

	i = 0;
	if(!tofree)
		return ;
	while(tofree[i])
		ft_free_char2(tofree[i++]);
	free(tofree);
}