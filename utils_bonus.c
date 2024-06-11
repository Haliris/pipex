/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:43:14 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/11 12:43:35 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

void	trash(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_str_rejoin(char *stash, char *add)
{
	char	*joined;

	if (!stash)
		return (NULL);
	joined = ft_calloc((ft_strlen(stash) + ft_strlen(add) + 1), sizeof(char));
	if (!joined)
		return (free(stash), NULL);
	copy_and_cat(joined, stash, add);
	return (free(stash), joined);
}

void	copy_and_cat(char *out, char *cpy_src, char *cat_src)
{
	size_t	i;
	int		src_i;

	src_i = 0;
	ft_strlcpy(out, cpy_src, ft_strlen(cpy_src) + 1);
	i = ft_strlen(out);
	while (cat_src[src_i])
		out[i++] = cat_src[src_i++];
	out[i] = '\0';
}
