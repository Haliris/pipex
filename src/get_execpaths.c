/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execpaths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:44:37 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/07 18:59:15 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"

void	cat_slash(char **exec_paths)
{
	int		i;
	char	*cat_path;
	size_t	len;

	i = 0;
	if (!exec_paths)
		return ;
	while (exec_paths[i])
	{
		len = ft_strlen(exec_paths[i]);
		cat_path = ft_calloc((len + 2), sizeof(char));
		if (!cat_path)
		{
			trash(exec_paths);
			return ;
		}
		ft_strlcpy(cat_path, exec_paths[i], len + 2);
		cat_path[len] = '/';
		free(exec_paths[i]);
		exec_paths[i] = cat_path;
		i++;
	}
}

char	**get_execpaths(char **envp)
{
	int		i;
	char	*env_path;
	char	**exec_paths;

	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		env_path = ft_strnstr(envp[i], "PATH=", 5);
		if (env_path)
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	if (!env_path)
		return (NULL);
	exec_paths = ft_split(env_path, ':');
	free(env_path);
	cat_slash(exec_paths);
	if (!exec_paths)
		return (NULL);
	return (exec_paths);
}
