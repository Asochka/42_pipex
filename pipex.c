/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smana <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:48:45 by smana             #+#    #+#             */
/*   Updated: 2022/04/12 19:48:52 by smana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_cmd(t_init *node, char **envp, char *argv2)
{
	if (dup2(node->fd1, STDIN_FILENO) < 0)
		ft_clean_node(node, "error with dup2()");
	if (dup2(node->end[1], STDOUT_FILENO) < 0)
		ft_clean_node(node, "error with dup2()");
	close(node->end[0]);
	execve(node->cmd1, ft_split(argv2, ' '), envp);
	close(node->fd1);
	close(node->end[1]);
	exit(EXIT_FAILURE);
}

void	ft_second_cmd(t_init *node, char **envp, char *argv3)
{
	if (dup2(node->end[0], STDIN_FILENO) < 0)
		ft_clean_node(node, "error with dup2()");
	if (dup2(node->fd2, STDOUT_FILENO) < 0)
		ft_clean_node(node, "error with dup2()");
	close(node->end[1]);
	execve(node->cmd2, ft_split(argv3, ' '), envp);
	close(node->fd2);
	close(node->end[0]);
	exit(EXIT_FAILURE);
}

void	ft_start_pipex(char **argv, char **envp, t_init *node)
{
	while (*argv[2] && *argv[2] == ' ')
		argv[2]++;
	if (!*argv[2])
		ft_error("ERROR: cmd1 doesn't exist");
	while (*argv[3] && *argv[2] == ' ')
		argv[3]++;
	if (!*argv[3])
		ft_error("ERROR: cmd2 doesn't exist");
	node = ft_init_node(argv, envp, node);
	if (pipe(node->end) == -1)
		ft_error("error with pipe");
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
