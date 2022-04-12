/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smana <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:48:33 by smana             #+#    #+#             */
/*   Updated: 2022/04/12 19:48:36 by smana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_init	node;

	if (argc == 5 && envp)
		ft_start_pipex(argv, envp, &node);
	else
		ft_error("error: wrong number of arguments");
	return (0);
}
