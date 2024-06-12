/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/12 17:30:40 by jteissie         ###   ########.fr       */
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
			handle_error(strerror(errno), errno);
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
		if (command)
			trash(command);
		handle_error("Command split error", EXIT_FAILURE);
	}
	try_direct_path(command, env);
	exec_path = get_execpath(env, command[0]);
	if (!exec_path)
	{
		trash(command);
		handle_error("Command not found", PATH_ERROR);
	}
	if (execve(exec_path, command, env) == -1)
	{
		free(exec_path);
		trash(command);
		handle_error(strerror(errno), errno);
	}
}

void	first_process(char **av, char **env, int *p_fd)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		handle_error(strerror(errno), errno);
	close(p_fd[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	execute(av[2], env);
}

void	second_process(char **av, char **env, int *p_fd)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		handle_error(strerror(errno), errno);
	close(p_fd[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	execute(av[3], env);
}

int	main(int ac, char *av[], char *envp[])
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;
	int		pid_status;

	if (ac < 5)
		handle_error("Error: Expected file1 cmd1 cmd2 file2", EXIT_FAILURE);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	pid2 = fork();
	if (pid < 0)
		handle_error("Could not fork first child", EXIT_FAILURE);
	if (pid2 < 0)
		handle_error("Could not fork second child", EXIT_FAILURE);
	if (pid == 0)
		first_process(av, envp, fd);
	if (pid2 == 0)
		second_process(av, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &pid_status, 0);
	waitpid(pid2, &pid_status, 0);
	if (pid_status)
		handle_error("Child exited early", EXIT_FAILURE);
	return (0);
}
