/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/14 19:58:07 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex_bonus.h"

void	marry_and_reproduce(char *cmd, char **env)
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
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
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

	fd = open(av, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		handle_error(strerror(errno), errno);
	return (fd);
}

int	main(int ac, char *av[], char *envp[])
{
	int		index;
	int		fd_in;
	int		fd_out;

	if (ac < 5)
		handle_error("Expected at least file1 cmd1 cmd2 file2", EXIT_FAILURE);
	fd_in = open_infile(av[1]);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	fd_out = open_outfile(av[ac - 1]);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	marry_and_reproduce(av[2], envp);
	index = 3;
	while (index < ac - 2)
	{
		marry_and_reproduce(av[index], envp);
		index++;
	}
	execute(av[ac - 2], envp);
	return (EXIT_SUCCESS);
}
