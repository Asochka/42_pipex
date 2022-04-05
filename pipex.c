#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5 && envp)
		ft_start_pipex(argc, argv, envp);
	else
		exit(EXIT_FAILURE);
	return (0);
}

char	**ft_parsing_path(char **envp)
{
	char **paths;
	int	i;

	i = 0;
	while ((envp[i]) && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	envp[i] += 5;
	paths = ft_split(envp[i], ":");
	return (path);
}

void	ft_check_cmd(char **paths, char *cmd)
{
	int	i;

	i = 0;
	
}
void child_process()
{
// int  i;
// char *cmd;

// i = -1;
// while (mypaths[++i])
// {
//     cmd = ft_join(mypaths[i], ag[2]); // protect your ft_join
//     execve(cmd, mycmdargs, envp); // if execve succeeds, it exits
//     // perror("Error"); <- add perror to debug
//     free(cmd) // if execve fails, we free and we try a new path
// }
// return (EXIT_FAILURE);
}




void	ft_start_pipex(int argc, char **argv, char **envp)
{
	t_init	*node;
	char	**path;

	path = ft_parsing_path(envp);
	node = (t_init *)malloc(sizeof(t_init));
	if (!node)
		exit(EXIT_FAILURE);
	node->fd1 = open(argv[1], O_RDONLY, 0777);
	node->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (node->fd1 < 0 || node->fd2 < 0)
		exit(EXIT_FAILURE);

	pipex(node->fd1, node->fd2, argv[2], argv[3]);
	return (0);
}

int	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int	end[2];
	int	status;
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
         return (perror("Fork: "));
    if (child1 == 0)
        child_one(f1, cmd1);
    child2 = fork();
    if (child2 < 0)
         return (perror("Fork: "));
    if (child2 == 0)
        child_two(f2, cmd2);
    close(end[0]);         // this is the parent
    close(end[1]);         // doing nothing
    waitpid(child1, &status, 0);  // supervising the children
    waitpid(child2, &status, 0);  // while they finish their tasks
}