#include "pipex.h"

void	ft_first_cmd(t_init *node, char **envp, char *argv2)
{
	dup2(node->fd1, STDIN_FILENO);//protect
	dup2(node->end[1], STDOUT_FILENO);//protect
	close(node->end[0]);
	execve(node->cmd1, ft_split(argv2, ' '), envp);
	close(node->fd1);
	close(node->end[1]);
	exit(EXIT_FAILURE);
}

void	ft_second_cmd(t_init *node, char **envp, char *argv3)
{
	dup2(node->end[0], STDIN_FILENO);//protect
	dup2(node->fd2, STDOUT_FILENO);//protect
	close(node->end[1]);
	execve(node->cmd2, ft_split(argv3, ' '), envp);
	close(node->fd2);
	close(node->end[0]);
	exit(EXIT_FAILURE);
}

void	ft_start_pipex(char **argv, char **envp)
{
	t_init	*node;

	if (pipe(node->end) == -1)
		ft_error("error with pipe");
	node = ft_init_node(argv, envp);
	node->child1 = fork();
	if (node->child1 < 0)
		ft_clean_node(node, "error with fork()");
	else if (node->child1 == 0)
		ft_first_cmd(node, envp, argv[2]);
	node->child2 = fork();
	if (node->child2 < 0)
		ft_clean_node(node, "error with fork()");
	else if (node->child2 == 0)
		ft_second_cmd(node, envp, argv[3]);
	waitpid(0, NULL, 0);
}
