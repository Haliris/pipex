/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:54:19 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/15 21:54:41 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

int	open_infile(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
		handle_error(strerror(errno), errno);
	return (fd);
}

int	open_outfile(char *av, int append)
{
	int	fd;

	if (append)
		fd = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		handle_error(strerror(errno), errno);
	return (fd);
}
