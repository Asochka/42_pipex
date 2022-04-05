/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:24:06 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:24:15 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_file_fd(char *file_dir, int is_first, t_fd t_fd)
{
	int	file_fd;

	if (is_first == 1)
	{
		if (t_fd.is_here_doc)
			file_fd = open(file_dir, O_CREAT | O_WRONLY | O_APPEND, 0777);
		else
			file_fd = open(file_dir, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	else
		file_fd = open(file_dir, O_RDONLY, 0777);
	return (file_fd);
}

/*
returns -1 in case of fork error
returns 0 in case of success
*/
int	first_cmd_call(char **first_str, char **path, t_fd t_fd, char **envp)
{
	int		pid;
	int		fd[2];

	pid = fork();
	if (pid < 0)
	{
		close(t_fd.fds[t_fd.i][1]);
		return (-1);
	}
	if (pid == 0)
	{
		fd[1] = dup(t_fd.fds[t_fd.i][1]);
		close_free_fds(t_fd, 1);
		fd[0] = get_file_fd(*(first_str), 0, t_fd);
		if (fd[1] == -1 || fd[0] == -1)
			fatal_error_free(*(first_str), path);
		cmd_process(*(first_str + 1), path, fd, envp);
	}
	close(t_fd.fds[t_fd.i][1]);
	waitpid(pid, NULL, 0);
	return (0);
}

/*
returns -1 in case of fork error
returns 0 in case of success
*/
int	last_cmd_call(char **last_str, char **path, t_fd t_fd, char **envp)
{
	int		pid;
	int		fd[2];

	pid = fork();
	if (pid < 0)
	{
		close(t_fd.fds[t_fd.i][0]);
		return (-1);
	}
	if (pid == 0)
	{
		fd[0] = dup(t_fd.fds[t_fd.i][0]);
		close_free_fds(t_fd, 0);
		fd[1] = get_file_fd(*(last_str + 1), 1, t_fd);
		if (fd[1] == -1 || fd[0] == -1)
			fatal_error_free(*(last_str + 1), path);
		cmd_process(*last_str, path, fd, envp);
	}
	close(t_fd.fds[t_fd.i][0]);
	waitpid(pid, NULL, 0);
	return (0);
}

/*
returns -1 in case of fork error
returns 0 in case of success
*/
int	cmd_call(char *str, char **path, t_fd t_fd, char **envp)
{
	int		pid;
	int		fd[2];

	pid = fork();
	if (pid < 0)
	{
		close(t_fd.fds[t_fd.i][0]);
		close(t_fd.fds[t_fd.i + 1][1]);
		return (-1);
	}
	if (pid == 0)
	{
		fd[0] = dup(t_fd.fds[t_fd.i][0]);
		fd[1] = dup(t_fd.fds[t_fd.i + 1][1]);
		close_free_fds(t_fd, 0);
		if (fd[1] == -1 || fd[0] == -1)
			fatal_error_free(str, path);
		cmd_process(str, path, fd, envp);
	}
	close(t_fd.fds[t_fd.i][0]);
	close(t_fd.fds[t_fd.i + 1][1]);
	waitpid(pid, NULL, 0);
	return (0);
}
