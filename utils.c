#include "pipex.h"

t_init	*ft_init_node(char **argv, char **envp)
{
	t_init	*node;

	node = (t_init *)malloc(sizeof(t_init));
	if (!node)
		ft_error("error with malloc");
	node->fd1 = open(argv[1], O_RDONLY, 0777);
	node->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (node->fd1 < 0 || node->fd2 < 0)
		ft_clean_node(node, "error with files");
	node->paths = ft_parsing_path(envp);
	if (!node->paths)
		ft_clean_node(node, "error with paths");
	node->cmd1 = ft_ckeck_cmd(argv[2], node->paths);
	node->cmd2 = ft_ckeck_cmd(argv[3], node->paths);
	if (!node->cmd1 || !node->cmd2)
		ft_clean_node(node, "error with commands");
	return (node);
}

void	ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}

void	ft_claen_node(t_init *node, char *s)
{
	int	i;

	if (node->cmd1)
		free(node->cmd1);
	if (node->cmd2)
		free(node->cmd2);
	if (node->paths)
	{
		i = 0;
		while (node->paths[i])
			free(node->paths[i++]);
		free(node->paths);
	}
	if (node->end)
		free(node->end);
	free(node);
	// if (node->cmd1_mass)
	// {
	// 	i = 0;
	// 	while (node->cmd1_mass[i])
	// 		free(node->cmd1_mass[i++]);
	// 	free(node->cmd1_mass);
	// }
	// if (node->cmd2_mass)
	// {
	// 	i = 0;
	// 	while (node->cmd2_mass[i])
	// 		free(node->cmd2_mass[i++]);
	// 	free(node->cmd2_mass);
	// }	
	ft_error(s);
}
