/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:27:26 by jobject           #+#    #+#             */
/*   Updated: 2021/11/15 14:45:08 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_1(t_cmd	*cmds, char	**envp, char	*filename
, t_proccess	*proc)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0777);
	if (fd < 0)
		error_cmd("ERROR: Unable to open 'infile'", &cmds);
	if (dup2(fd, STDIN_FILENO) < 0)
		error_cmd("ERROR: Unable to dup infile and STDIN", &cmds);
	if (dup2(proc->fds[1], STDOUT_FILENO) < 0)
		error_cmd("ERROR: Unable to dup fds[1] and STDOUT", &cmds);
	close(proc->fds[0]);
	execve(cmds->cmd1_path, cmds->cmd1, envp);
	close(fd);
	close(proc->fds[1]);
	exit(EXIT_FAILURE);
}

void	child_2(t_cmd	*cmds, char	**envp, char	*filename
, t_proccess	*proc)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (dup2(proc->fds[0], STDIN_FILENO) < 0)
		error_cmd("ERROR: Unable to dup fds[0] and STDIN", &cmds);
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_cmd("ERROR: Unable to dup outfile and STDOUT", &cmds);
	close (proc->fds[1]);
	execve(cmds->cmd2_path, cmds->cmd2, envp);
	close(fd);
	close(proc->fds[0]);
	exit(EXIT_FAILURE);
}

void	pipex(t_cmd	*cmds, t_proccess	*proc, char	**envp, char	**argv)
{
	proc->child1 = fork();
	if (proc->child1 < 0)
		error_cmd("ERROR: Forking one failed", &cmds);
	if (!proc->child1)
		child_1(cmds, envp, argv[1], proc);
	proc->child2 = fork();
	if (proc->child2 < 0)
		error_cmd("ERROR: Forking two failed", &cmds);
	if (!proc->child2)
		child_2(cmds, envp, argv[4], proc);
	waitpid(0, NULL, 0);
}
