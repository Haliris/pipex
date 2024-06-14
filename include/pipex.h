/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/14 10:58:31 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# define PATH_ERROR 127
# define EXIT_FAILURE 1

char	*get_execpath(char **envp, char *av);
void	cat_slash(char **envp);
void	trash(char **array);
char	*ft_str_rejoin(char *stash, char *add);
void	copy_and_cat(char *out, char *cpy_src, char *cat_src);
char	*get_path(char *av, char **env);
void	handle_error(char *message, int code);
void	try_absolute_path(char **command, char **env);
void	execute(char *av, char **env);
#endif
