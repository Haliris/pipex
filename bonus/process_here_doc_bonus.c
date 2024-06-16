/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_here_doc_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:09:14 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/16 12:29:21 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include "get_next_line.h"

void	put_line(char *limiter)
{
	char	*gnl_line;
	int		len;

	len = ft_strlen(limiter);
	while (1)
	{
		gnl_line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(gnl_line, limiter, len) == 0 && gnl_line[len] == '\n')
		{
			free(gnl_line);
			exit(EXIT_SUCCESS);
		}
		if (!gnl_line)
			handle_error("Couldn't find LIMITER in here_doc", EXIT_FAILURE);
		ft_putstr_fd(gnl_line, STDOUT_FILENO);
		free(gnl_line);
	}
}

void	process_here_doc(char *limiter)
{
	int		p_fd[2];
	pid_t	pid_child;
	int		status;

	if (pipe(p_fd) == -1)
		handle_error("Could not open pipe for here_doc child", errno);
	pid_child = fork();
	if (pid_child < -1)
		handle_error("Could not fork here_doc child", errno);
	if (pid_child == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
		put_line(limiter);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
		waitpid(pid_child, &status, 0);
		if (status)
			handle_error("Here_doc child exited early", EXIT_FAILURE);
	}
}
