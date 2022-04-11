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
	int		fd1;
	int		fd2;

	pid_t	child1;
	pid_t	child2;
	int		end[2];

	char	*cmd1;
	char	*cmd2;
	char	**paths;
}	t_init;

char	**ft_parsing_path(char **envp);
char	*ft_check_cmd(char *argv, char **paths);

void	ft_start_pipex(char **argv, char **envp);
void	ft_first_cmd(t_init *node, char **envp, char *argv2);
void	ft_second_cmd(t_init *node, char **envp, char *argv3);

void	ft_clean_node(t_init *node, char *s);
void	ft_error(char *s);
t_init	*ft_init_node(char **argv, char **envp);
void	ft_free(char **str);

#endif