/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/08 19:55:45 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	try_direct_path(char **command, char **env)
{
	char	*exec_path;

	if (access(command[0], F_OK | X_OK) == 0)
	{
		exec_path = command[0];
		if (execve(exec_path, command, env) == -1)
		{
			trash(command);
			perror("Child process error: ");
			exit (-1);
		}
	}
}

void	execute(char *av, char **env)
{
	char	**command;
	char	*exec_path;

	command = ft_split(av, ' ');
	if (!command || !command[0])
	{
		perror("Child process error: ");
		exit (1);
	}
	try_direct_path(command, env);
	exec_path = get_execpath(env, command[0]);
	if (!exec_path)
	{
		trash(command);
		perror("Child process error: ");
		exit (1);
	}
	if (execve(exec_path, command, env) == -1)
	{
		free(exec_path);
		trash(command);
		perror("Child process error: ");
		exit (-1);
	}
}

void	first_process(char **av, char **env, int *p_fd)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("Child process");
		exit(errno);
	}
	close(p_fd[0]);
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	execute(av[2], env);
}

void	second_process(char **av, char **env, int *p_fd)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Child process");
		exit(errno);
	}
	close(p_fd[1]);
	dup2(fd, STDOUT_FILENO);
	dup2(p_fd[0], STDIN_FILENO);
	execute(av[3], env);
}

int	main(int ac, char *av[], char *envp[])
{
	int		fd[2];
	pid_t	pid1;
	int		pid_status;

	if (ac < 5)
	{
		ft_putstr_fd("Error: Expected file1 cmd1 cmd2 file2\n", 2);
		exit(1);
	}
	if (pipe(fd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 < 0)
		exit(1);
	if (pid1 == 0)
		first_process(av, envp, fd);
	waitpid(pid1, &pid_status, 0);
	if (pid_status)
	{
		ft_printf("Child exited with code:%d\n", pid_status);
		exit(1);
	}
	second_process(av, envp, fd);
	return (0);
}
