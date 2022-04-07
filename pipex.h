#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_init
{
	int		fd1;//in
	int		fd2;//out
	pid_t	child1;
	pid_t	child2;
	int		end[2];//fds
	char	**cmd1;
	char	**cmd2;
	char	**paths;
}	t_init;

#endif