/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/16 12:16:56 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# define PATH_ERROR 127
# define EXIT_FAILURE 1
# define APPEND_TRUE 1
# define APPEND_FALSE 0
# define LAST_FILE 1

char	*get_execpath(char **envp, char *av);
void	cat_slash(char **envp);
void	trash(char **array);
void	copycat_str(char *out, char *cpy_src, char *cat_src);
char	*get_path(char *av, char **env);
char	*ft_str_realloc_join(char *stash, char *add);
void	handle_error(char *message, int code);
void	try_absolute_path(char **command, char **env);
void	execute(char *av, char **env);
void	process_here_doc(char *limiter);
int		open_infile(char *av);
int		open_outfile(char *av, int append);
#endif
