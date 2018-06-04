/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:35:11 by ltanenba          #+#    #+#             */
/*   Updated: 2018/04/20 18:18:54 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static t_list				*st_get_file(t_list **file, int fd)
{
	t_list			*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(file, tmp);
	return (*file);
}

static char					*st_strsub_free(char *s, unsigned int i)
{
	char			*tmp;

	tmp = ft_strsub(s, i, ft_strlen(s + i));
	free(s);
	return (tmp);
}

static int					st_filedel(t_list **flist, int fd)
{
	t_list			*tmp;
	t_list			*prev;

	tmp = *flist;
	if ((int)tmp->content_size == fd)
	{
		*flist = tmp->next;
		free(tmp->content);
		free(tmp);
	}
	else
		while (tmp->next)
		{
			prev = tmp;
			tmp = tmp->next;
			if ((int)tmp->content_size == fd)
			{
				prev->next = tmp->next;
				free(tmp->content);
				free(tmp);
				break ;
			}
		}
	return (0);
}

int							get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				read_num;
	int				i;
	t_list			*file;
	static t_list	*flist;

	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	file = st_get_file(&flist, fd);
	while ((read_num = read(fd, buf, BUFF_SIZE)))
	{
		buf[read_num] = '\0';
		GNL_MALLOC_CHECK(ft_strjoin_free((char **)&(file->content), buf));
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (read_num < BUFF_SIZE && ft_strlen(file->content) == 0)
		return (st_filedel(&flist, fd));
	i = ft_copyuntil(line, file->content, '\n');
	if (i < (int)ft_strlen(file->content))
		file->content = st_strsub_free(file->content, i + 1);
	else
		ft_strclr(file->content);
	return (1);
}
