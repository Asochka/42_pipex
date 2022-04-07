#include "pipex.h"

char	**ft_parsing_path(char **envp)
{
	char **paths;
	int	i;

	i = 0;
	while ((envp[i]) && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

char	*ft_check_cmd(char *argv, char **paths)
{
	int		i;
	char	**raw_cmd;
	char	*cmd;

	i = -1;
	raw_cmd = ft_split(argv, ' ');
	while (paths[++i])
	{
    	cmd = ft_join(paths[i], raw_cmd[0]);
		if (!access(cmd, F_OK))
	}
	return (cmd);		
}

t_init	*ft_init_node(char **argv, char **envp)
{
	t_init	*node;

	node = (t_init *)malloc(sizeof(t_init));
	if (!node)
		exit(EXIT_FAILURE);
	node->fd1 = open(argv[1], O_RDONLY, 0777);
	node->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (node->fd1 < 0 || node->fd2 < 0)
		exit(EXIT_FAILURE);//free
	node->paths = ft_parsing_path(envp);
	node->cmd1 = ft_ckeck_cmd(argv[2], node->paths);
	node->cmd2 = ft_ckeck_cmd(argv[3], node->paths);
	if (!node->cmd1 || !node->cmd2)
		exit(EXIT_FAILURE);//free
	return (node);
}

// int	first_cmd()
// {
// 	int	pid;
// 	int	fd[2];

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		close()
// 	}
// }

void	ft_start_pipex(char **argv, char **envp)
{
	t_init	*node;

	node = ft_init_node(argv, envp);
	if (pipe(node->end) == -1)
		exit(EXIT_FAILURE);//free
//	ft_check_cmd(&node, envp);
	
}

int	pipex(t_init *node, char *cmd1, char *cmd2)
{

// 	int	status;
// 	pid_t	child1;
// 	pid_t	child2;

// 	pipe(end);
// 	child1 = fork();
// 	if (child1 < 0)
//          return (perror("Fork: "));
//     if (child1 == 0)
//         child_one(f1, cmd1);
//     child2 = fork();
//     if (child2 < 0)
//          return (perror("Fork: "));
//     if (child2 == 0)
//         child_two(f2, cmd2);
//     close(end[0]);         // this is the parent
//     close(end[1]);         // doing nothing
//     waitpid(child1, &status, 0);  // supervising the children
//     waitpid(child2, &status, 0);  // while they finish their tasks
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5 && envp)
		ft_start_pipex(argv, envp);
	else
		exit(EXIT_FAILURE);
	return (0);
}