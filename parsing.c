/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smana <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:48:59 by smana             #+#    #+#             */
/*   Updated: 2022/04/12 19:49:01 by smana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_parsing_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while ((envp[i]) && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

char	*ft_check_cmd(char *argv, char **paths)
{
	int		i;
	char	**raw_cmd;
	char	*cmd;

	i = 0;
	raw_cmd = ft_split(argv, ' ');
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], raw_cmd[0]);
		if (!cmd)
			ft_error("error: strjoin tmp");
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			free(cmd);
		i++;
	}
	ft_free(raw_cmd);
	return (NULL);
}
