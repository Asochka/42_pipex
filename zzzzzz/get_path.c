/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:23:43 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:24:19 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	add_slashes(char **path)
{
	int		i;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = path[i];
		path[i] = ft_strjoin(temp, "/");
		free(temp);
		if (!path[i])
			return (-1);
		i++;
	}
	return (0);
}

char	**get_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		return (NULL);
	if (add_slashes(path) == -1)
	{
		free_two_dim(path);
		return (NULL);
	}
	return (path);
}
