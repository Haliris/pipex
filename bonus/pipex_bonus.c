/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/15 18:55:40 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex_bonus.h"

void	redirect(int *p_fd, int *file_fd, int mode)
{
	close(p_fd[0]);
	if (mode)
	{
		dup2(file_fd[1], STDOUT_FILENO);
	}
	else
		dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	close(file_fd[1]);
	close(file_fd[0]);
}

void	marry_and_reproduce(char *cmd, char **env, int *fd, int mode)
{
	int	pid_child;
	int	p_fd[2];

	if (pipe(p_fd) == -1)
		handle_error("Could not open pipe for middle child", EXIT_FAILURE);
	pid_child = fork();
	if (pid_child < 0)
		handle_error("Could not fork middle child", EXIT_FAILURE);
	if (pid_child == 0)
	{
		redirect(p_fd, fd, mode);
		execute(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
	}
}

int	open_infile(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
		handle_error(strerror(errno), errno);
	return (fd);
}

int	open_outfile(char *av)
{
	int	fd;

	fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		handle_error(strerror(errno), errno);
	return (fd);
}

void	wait_for_children(int index, int *p_fd)
{
	int	status;

	close(p_fd[0]);
	close(p_fd[1]);
	while (index >= 2)
	{
		wait(&status);
		if (status)
			perror("Child exit status");
		index--;
	}
}

int	main(int ac, char *av[], char *envp[])
{
	int		index;
	int		fd_file[2];

	if (ac < 5)
		handle_error("Expected at least file1 cmd1 cmd2 file2", EXIT_FAILURE);
	index = 2;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		process_here_doc(av[2]);
		index++;
	}
	else
	{
		fd_file[0] = open_infile(av[1]);
		dup2(fd_file[0], STDIN_FILENO);
	}
	fd_file[1] = open_outfile(av[ac - 1]);
	dup2(fd_file[1], STDOUT_FILENO);
	marry_and_reproduce(av[index++], envp, fd_file, 0);
	while (index < ac - 2)
		marry_and_reproduce(av[index++], envp, fd_file, 0);
	marry_and_reproduce(av[ac - 2], envp, fd_file, 1);
	wait_for_children(index, fd_file);
	return (EXIT_SUCCESS);
}
