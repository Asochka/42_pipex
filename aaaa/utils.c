/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:27:06 by jobject           #+#    #+#             */
/*   Updated: 2021/11/15 18:50:17 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(char	*message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

static void	delete_structure(char	**strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	del(t_cmd	*cmds)
{
	delete_structure(cmds->cmd1);
	delete_structure(cmds->cmd2);
	delete_structure(cmds->mypaths);
	free(cmds->cmd1_path);
	free(cmds->cmd2_path);
}

void	error_cmd(char	*message, t_cmd	**cmds)
{
	delete_structure((*cmds)->cmd1);
	delete_structure((*cmds)->cmd2);
	delete_structure((*cmds)->mypaths);
	if ((*cmds)->cmd1_path)
		free((*cmds)->cmd1_path);
	if ((*cmds)->cmd2_path)
		free((*cmds)->cmd2_path);
	error_message(message);
}

char	*double_join(char	*s1, char	*s2)
{
	char	*temp1;
	char	*res;

	temp1 = ft_strjoin(s1, "/");
	res = ft_strjoin(temp1, s2);
	free(temp1);
	return (res);
}
