/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:23:59 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:24:14 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	change_fds(int *fd)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (-1);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (-1);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

static void	execute(char **cmd_args, char **envp, char **path, char *cmd_dir)
{
	free_two_dim(path);
	free(cmd_dir);
	execve(cmd_args[0], cmd_args, envp);
}

/*
returns 1 in case of other errors
returns 2 in case of malloc error
*/
int	go_through_path(char **path, char **cmd_args, char **envp)
{
	char	*cmd_dir;
	int		i;

	i = 0;
	cmd_dir = ft_strdup(cmd_args[0]);
	if (!cmd_dir)
		return (2);
	if (path)
	{
		while (path[i])
		{
			free(cmd_args[0]);
			cmd_args[0] = ft_strjoin(path[i], cmd_dir);
			if (!cmd_args[0])
			{
				free(cmd_dir);
				return (2);
			}
			if (access(cmd_args[0], X_OK) == 0)
				execute(cmd_args, envp, path, cmd_dir);
			i++;
		}
	}
	free(cmd_dir);
	return (1);
}

/*
returns 1 in case of other errors
returns 2 in case of malloc error
*/
static int	cmd_run(char **cmd_args, char **path, int *fd, char **envp)
{
	if (change_fds(fd) == -1)
		return (1);
	if (access(cmd_args[0], X_OK) == 0)
	{
		free_two_dim(path);
		execve(cmd_args[0], cmd_args, envp);
	}
	if (go_through_path(path, cmd_args, envp) == 2)
		return (2);
	return (1);
}

void	cmd_process(char *str, char **path, int *fd, char **envp)
{
	char	**cmd_args;
	int		cmd_result;
	char	*file_dir;

	cmd_args = ft_split(str, ' ');
	if (!cmd_args)
		memory_error_free(path);
	file_dir = ft_strdup(cmd_args[0]);
	if (!file_dir)
	{
		free_two_dim(cmd_args);
		memory_error_free(path);
	}
	cmd_result = cmd_run(cmd_args, path, fd, envp);
	if (cmd_result == 1)
		perror(file_dir);
	else
		ft_putstr_fd("Could not allocate memory\n", 2);
	free(file_dir);
	free_two_dim(cmd_args);
	free_two_dim(path);
	close(fd[0]);
	close(fd[1]);
	exit(1);
}
