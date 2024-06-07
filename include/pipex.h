/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/07 22:28:34 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

char	*get_execpath(char **envp, char *av);
void	cat_slash(char **envp);
void	trash(char **array);
char	*ft_str_rejoin(char *stash, char *add);
void	copy_and_cat(char *out, char *cpy_src, char *cat_src);
char	*get_path(char *av, char **env);
#endif
