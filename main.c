/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/07 16:26:44 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

// /usr/bin/argv[1] issue with arguments

char	*clean_path(char *str)
{
	size_t		i;
	size_t		new_i;
	char		*cleaned_str;

	if (!str)
		return(NULL);
	i = 0;
	new_i = 0;
	while(str[i] != '=')
		i++;
	i++;
	cleaned_str = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!cleaned_str)
		return (free(str), NULL);
	ft_strlcpy(cleaned_str, &str[i], ft_strlen(str) - i + 1);
	return (free(str), cleaned_str);
}

char	**get_execpaths(char **envp)
{
	int		i;
	char	*env_path;
	char	**exec_paths;

	i = 0;
	env_path = NULL;
	while(envp[i])
	{
		env_path = ft_strnstr(envp[i], "PATH=", 5);	
		if (env_path)
		{
			env_path = ft_strdup(envp[i]);
			break ;
		}
		i++;
	}
	env_path = clean_path(env_path);
	if(!env_path)
		return (NULL);
	exec_paths = ft_split(env_path, ':');
	free(env_path);
	if (!exec_paths)
		return (NULL);
	return (exec_paths);
}

int	main(int ac, char *av[], char *envp[])
{
	char	**exec_paths;
	int		i;

	i = 0;
	exec_paths = get_execpaths(envp);	
	if (!exec_paths)
		return (1);
	while(exec_paths[i])	
	{
		ft_printf("%s\n", exec_paths[i]);
		i++;
	}
	i = 0;
	while (exec_paths[i])
	{
		free(exec_paths[i]);
		i++;
	}
	free(exec_paths);
	return (0);
}
