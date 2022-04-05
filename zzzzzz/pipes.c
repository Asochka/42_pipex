/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:23:35 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:25:21 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	**allocate_fds(int argc)
{
	int	i;
	int	**fds;

	fds = (int **) malloc(sizeof(int *) * (argc - 4 + 1));
	if (!fds)
		return (NULL);
	i = 0;
	while (i < argc - 4)
	{
		fds[i] = (int *) malloc(sizeof(int) * 2);
		if (!fds[i])
		{
			free_two_dim_int_part(fds, i);
			return (NULL);
		}
		i++;
	}
	fds[argc - 4] = NULL;
	return (fds);
}

int	**open_pipes(int argc, char **argv)
{
	int	**fds;
	int	i;

	if (ft_strncmp("here_doc", argv[1], 8) == 0 && ft_strlen(argv[1]) == 8)
		argc++;
	fds = allocate_fds(argc);
	if (!fds)
		return (NULL);
	i = 0;
	while (fds[i])
	{
		if (pipe(fds[i]) == -1)
		{
			free_two_dim_int(fds);
			return (NULL);
		}
		i++;
	}
	return (fds);
}

void	close_free_fds(t_fd t_fd, int is_first)
{
	int	j;

	if (is_first)
		close(t_fd.fds[t_fd.i][1]);
	close(t_fd.fds[t_fd.i][0]);
	t_fd.i++;
	while (t_fd.fds[t_fd.i])
	{
		j = 0;
		while (j < 2)
			close(t_fd.fds[t_fd.i][j++]);
		t_fd.i++;
	}
	free_two_dim_int(t_fd.fds);
}
