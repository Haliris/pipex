/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/07 22:39:06 by jteissie         ###   ########.fr       */
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

void	execute(char *av, char **env)
{
	char	**command;
	char	*exec_path;

	command = ft_split(av, ' ');
	if (!command)
		return ;
	exec_path = get_execpath(env, command[0]);
	if (!exec_path)
	{
		trash(command);
		return ;
	}
	if (execve(exec_path, command, env) == -1)
	{
		free(exec_path);
		trash(command);
		return ;
	}
}
void	first_process(char **av, char **env, int *p_fd)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	close(p_fd[0]);
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	execute(av[2], env);
}

void	second_process(char **av, char **env, int *p_fd)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC);
	close(p_fd[1]);
	dup2(fd, STDOUT_FILENO);
	dup2(p_fd[0], STDIN_FILENO);
	execute(av[3], env);
}

int	main(int ac, char *av[], char *envp[])
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
		first_process(av, envp, fd);
	waitpid(pid1, NULL, 0);
	second_process(av, envp, fd);
	return (0);

}
//exec_paths[i]/av[1];
//
// while (exec_paths[i])
// {
//		ft_printf("%s\n", exec_paths[i]);
//		i++;
// }
