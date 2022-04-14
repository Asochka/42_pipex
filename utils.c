/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smana <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:49:07 by smana             #+#    #+#             */
/*   Updated: 2022/04/12 19:49:10 by smana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_init	*ft_init_node(char **argv, char **envp, t_init *node)
{
	node->fd1 = open(argv[1], O_RDONLY, 0777);
	if (node->fd1 < 0)
		ft_clean_node(node, "error with files");
	node->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (node->fd2 < 0)
		ft_clean_node(node, "error with files");
	node->paths = ft_parsing_path(envp);
	if (!node->paths)
		ft_clean_node(node, "error with paths");
	node->cmd1 = ft_check_cmd(argv[2], node->paths);
	node->cmd2 = ft_check_cmd(argv[3], node->paths);
	if (!node->cmd1 || !node->cmd2)
		ft_putendl_fd("command not found", 2);
	return (node);
}

void	ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}

void	ft_clean_node(t_init *node, char *s)
{
	if ((node)->cmd1)
		free((node)->cmd1);
	if ((node)->cmd2)
		free((node)->cmd2);
	if ((node)->paths)
		ft_free((node)->paths);
	if (s)
		ft_error(s);
}

void	ft_free(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
