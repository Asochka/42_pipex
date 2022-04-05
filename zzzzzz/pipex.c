/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:23:27 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:26:19 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char **argv, char **path, int argc, char **envp)
{
	int		i;
	t_fd	t_fd;

	i = 1;
	t_fd.i = 0;
	t_fd.is_here_doc = 0;
	t_fd.fds = open_pipes(argc, argv);
	if (!t_fd.fds)
		fatal_error_free("pipe", path);
	if (first_cmd_call(argv + i, path, t_fd, envp) == -1)
		perror("fork");
	i += 2;
	if (last_cmd_call(argv + i, path, t_fd, envp) == -1)
		perror("fork");
	free_two_dim(path);
	free_two_dim_int(t_fd.fds);
}
