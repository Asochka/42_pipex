/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:27:32 by jobject           #+#    #+#             */
/*   Updated: 2021/11/15 20:00:25 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_cmd_path(t_cmd	**cmds)
{
	int		i;

	i = 0;
	while ((*cmds)->mypaths[i])
	{
		(*cmds)->cmd1_path = double_join((*cmds)->mypaths[i], (*cmds)->cmd1[0]);
		if (!access((*cmds)->cmd1_path, F_OK))
			break ;
		free((*cmds)->cmd1_path);
		(*cmds)->cmd1_path = NULL;
		i++;
	}
	i = 0;
	while ((*cmds)->mypaths[i])
	{
		(*cmds)->cmd2_path = double_join((*cmds)->mypaths[i], (*cmds)->cmd2[0]);
		if (!access((*cmds)->cmd2_path, F_OK))
			break ;
		free((*cmds)->cmd2_path);
		(*cmds)->cmd2_path = NULL;
		i++;
	}
}

void	check(char	**argv)
{
	while (*argv[2] && *argv[2] == ' ')
		argv[2]++;
	if (!*argv[2])
		error_message("ERROR: cmd1 doesn't exist");
	while (*argv[3] && *argv[2] == ' ')
		argv[3]++;
	if (!*argv[3])
		error_message("ERROR: cmd2 doesn't exist");
}

void	init_cmd(char	**envp, char	**argv, t_cmd	*cmds)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], ft_strlen("PATH")))
		i++;
	if (envp[i])
		cmds->mypaths = ft_split(envp[i] + 5, ':');
	cmds->cmd1 = ft_split(argv[2], ' ');
	cmds->cmd2 = ft_split(argv[3], ' ');
	init_cmd_path(&cmds);
	if (!cmds->cmd1_path && !cmds->cmd2_path)
		error_cmd("ERROR: cmd1 and cmd2 don't exist", &cmds);
	if (!cmds->cmd1_path)
		error_cmd("ERROR: cmd1 doesn't exist", &cmds);
	if (!cmds->cmd2_path)
		error_cmd("ERROR: cmd2 doesn't exist", &cmds);
}
