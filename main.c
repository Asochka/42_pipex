#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5 && envp)
		ft_start_pipex(argv, envp);
	else
		ft_error("error: wrong number of arguments");
	return (0);
}