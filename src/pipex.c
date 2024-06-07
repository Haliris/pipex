/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/07 19:57:59 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
// /usr/bin/argv[1] issue with arguments


char	*get_command(char *str)
{
	int 	i;
	char	*command;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	command = ft_calloc(i + 1, sizeof(char));
	if (!command)
		return (NULL);
	ft_strlcpy(command, str, i + 1);
	return (command);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*exec_path;
	char	*command;
	char	**command_needs;
	int	i = 0;

	command = get_command(av[2]);
	if (!command)
		return (1);
	exec_path = get_execpath(command,envp);
	if (!exec_path)
	{
		free(command);
		return (1);
	}
	command_needs = ft_split(&av[2][ft_strlen(command) + 1], ' ');
	while (exec_paths[i])
	{
		ft_printf("%s\n", exec_paths[i]);
		i++;
	}
	if (!command_needs)
	{
		free(command);
		free(exec_path);
		return (1);
	}
	free(command);
	free(exec_path);
	trash(command_needs);
	return (0);
}
//exec_paths[i]/av[1];
//
// while (exec_paths[i])
// {
//		ft_printf("%s\n", exec_paths[i]);
//		i++;
// }
