/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:25:01 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:25:04 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"

typedef struct s_fd	t_fd;

struct s_fd
{
	int	**fds;
	int	i;
	int	is_here_doc;
};

//pipex
void	pipex(char **argv, char **path, int argc, char **envp);

//array utils
void	free_two_dim(char **arr);
void	free_two_dim_int(int **arr);
void	free_two_dim_int_part(int **arr, int i);

//pipes
int		**open_pipes(int argc, char **argv);
void	close_free_fds(t_fd t_fd, int is_first);

//path
char	**get_path(char **envp);

//cmd_call
int		cmd_call(char *str, char **path, t_fd t_fd, char **envp);
void	cmd_process(char *str, char **path, int *fd, char **envp);

//file cmd call
int		first_cmd_call(char **first_str, char **path, t_fd t_fd, char **envp);
int		last_cmd_call(char **last_str, char **path, t_fd t_fd, char **envp);

//errors
void	memory_error_free(char **path);
void	fatal_error_free(char *str, char **path);

//here_doc
int		here_doc_call(char **argv, char **path, t_fd t_fd, char **envp);

#endif