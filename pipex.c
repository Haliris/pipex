/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/13 17:33:52 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	first_process(char **av, char **env, int *p_fd)
{
	int	fd;
	int	error;

	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		handle_error(strerror(errno), errno);
	}
	close(p_fd[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	execute(av[2], env);
	error = execute(av[2], env);
	if (error)
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
	}
	handle_error(strerror(error), error);
}

void	second_process(char **av, char **env, int *p_fd)
{
	int	fd;
	int	error;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		handle_error(strerror(errno), errno);
	}
	close(p_fd[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	error = execute(av[3], env);
	if (error)
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
	}
	handle_error(strerror(error), error);
}

void	wait_for_children(int pid1, int pid2, int pid_status, int fd[])
{
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &pid_status, 0);
	waitpid(pid2, &pid_status, 0);
	if (pid_status)
		handle_error("Child exited early", EXIT_FAILURE);
}

int	main(int ac, char *av[], char *envp[])
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		pid_status;

	if (ac != 5)
		handle_error("Error: Expected file1 cmd1 cmd2 file2", EXIT_FAILURE);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 < 0)
		handle_error("Could not fork first child", EXIT_FAILURE);
	if (pid1 == 0)
		first_process(av, envp, fd);
	pid2 = fork();
	if (pid2 < 0)
		handle_error("Could not fork second child", EXIT_FAILURE);
	if (pid2 == 0)
		second_process(av, envp, fd);
	pid_status = 0;
	wait_for_children(pid1, pid2, pid_status, fd);
	return (EXIT_SUCCESS);
}
