/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:27:23 by jobject           #+#    #+#             */
/*   Updated: 2021/11/15 20:00:41 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_cmd
{
	char	**cmd1;
	char	**cmd2;
	char	**mypaths;
	char	*cmd1_path;
	char	*cmd2_path;
}				t_cmd;

typedef struct s_proccess
{
	int		fds[2];
	pid_t	child1;
	pid_t	child2;
}				t_proccess;

void	error_message(char	*message);
void	error_cmd(char	*message, t_cmd	**cmds);
char	*double_join(char	*s1, char	*s2);
void	init_cmd(char	**envp, char	**argv, t_cmd	*cmds);
void	pipex(t_cmd	*cmds, t_proccess	*proc, char	**envp, char	**argv);
void	del(t_cmd	*cmds);
void	init_cmd_path(t_cmd	**cmds);
void	check(char	**argv);

#endif