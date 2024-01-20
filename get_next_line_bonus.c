/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:07:32 by marvin            #+#    #+#             */
/*   Updated: 2024/01/20 20:01:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*remain_stat(char **stat, int fd)
{
	int		i;
	int		start;
	char	*remain;

	i = 0;
	if (stat[fd][i] == '\0')
	{
		free(stat[fd]);
		return (NULL);
	}
	while (stat[fd][i] != '\n' && stat[fd][i])
		i++;
	if (stat[fd][i] == '\n')
		i++;
	start = i;
	i = 0;
	remain = (char *)malloc((ft_strlen(stat[fd]) - start + 1) * sizeof(char));
	if (!remain)
		return (NULL);
	start--;
	while (stat[fd][++start])
		remain[i++] = stat[fd][start];
	remain[i] = '\0';
	free(stat[fd]);
	return (remain);
}

static char	*get_line(char	**stat, int fd)
{
	long	i;
	long	len;
	char	*line;

	i = 0;
	len = 0;
	if (stat[fd][i] == 0)
		return (NULL);
	while (stat[fd][len] != '\n' && stat[fd][len])
		len++;
	if (stat[fd][len] == '\n')
		len++;
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (i < len)
	{
		line[i] = stat[fd][i];
		i++;
	}
	return (line);
}

static char	*putstat(int fd, char **stat)
{
	int		val;
	char	*buf;

	val = 1;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (!charset(stat[fd]) && val != 0)
	{
		val = read(fd, buf, BUFFER_SIZE);
		if (val < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[val] = '\0';
		stat[fd] = strjoin(stat[fd], buf);
		if (!stat[fd])
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (stat[fd]);
}

char	*get_next_line(int fd)
{
	static char	*stat[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat[fd] = putstat(fd, stat);
	if (!stat[fd])
	{
		free(stat[fd]);
		return (NULL);
	}
	line = get_line(stat, fd);
	stat[fd] = remain_stat(stat, fd);
	if (!stat[fd])
	{
		free(line);
		return (NULL);
	}
	return (line);
}
