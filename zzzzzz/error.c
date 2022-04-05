/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:23:46 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:23:55 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fatal_error_free(char *str, char **path)
{
	free_two_dim(path);
	perror(str);
	exit(1);
}

void	memory_error_free(char **path)
{
	free_two_dim(path);
	ft_putstr_fd("Could not allocate memory\n", 2);
	exit(1);
}
