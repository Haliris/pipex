/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/07 18:57:01 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
// /usr/bin/argv[1] issue with arguments


int	main(int ac, char *av[], char *envp[])
{
	char	**exec_paths;
	char	**command_needs;
	int	i = 0;

	exec_paths = get_execpaths(envp);
	if (!exec_paths)
		return (1);
	//command_needs  ft_split(av[2], ' ');
	//safety here
	//trash(command_needs);
	if (exec_paths)
		trash(exec_paths);
	return (0);
}
//exec_paths[i]/av[1];
//
