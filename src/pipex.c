/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/07 16:52:26 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
// /usr/bin/argv[1] issue with arguments


int	main(int ac, char *av[], char *envp[])
{
	char	**exec_paths;

	exec_paths = get_execpaths(envp);	
	free(exec_paths);
	return (0);
}
//exec_paths[i]/av[1];
//
