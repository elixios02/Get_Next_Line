/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paim <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 14:22:25 by paim              #+#    #+#             */
/*   Updated: 2016/10/10 16:51:07 by paim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			bn(char **line, char **abn, char *buf)
{
	if (*abn == NULL)
	{
		*line = NULL;
		return (0);
	}
	if (*abn[0] == '\0')
	{
		*line = NULL;
		return (0);
	}
	if ((buf = ft_strchr(*abn, '\n')) == NULL)
	{
		*line = ft_strdup(*abn);
		*abn = NULL;
		return (1);
	}
	*buf = '\0';
	*line = ft_strdup(*abn);
	*buf = '\n';
	*abn = ft_strdup(buf + 1);
	return (1);
}

static int	read_me(int fd, char **line)
{
	static char	*abn[256];
	char		*tmp;
	char		buf[BUFF_SIZE + 1];
	int			ret;

	tmp = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (abn[fd] == NULL)
			abn[fd] = ft_strnew(0);
		tmp = abn[fd];
		abn[fd] = ft_strjoin(abn[fd], buf);
		ft_strdel(&tmp);
		if ((tmp = ft_strchr(abn[fd], '\n')) != NULL)
			break ;
	}
	if (ret == -1)
		return (-1);
	return (bn(line, &abn[fd], tmp));
}

int			get_next_line(int const fd, char **line)
{
	if (fd < 0)
		return (-1);
	return (read_me(fd, line));
}
