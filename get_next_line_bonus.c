/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:27:01 by llord             #+#    #+#             */
/*   Updated: 2022/06/13 13:57:56 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	has_line(char *doc)
{
	int	i;

	i = 0;
	if (doc)
	{
		while (doc[i])
		{
			if (doc[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

static char	*read_next_line(int fd, char *doc, int *flag)
{
	char	*temp;
	int		len;

	len = BUFFER_SIZE;
	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (doc && temp)
	{
		while (!has_line(doc) && len == BUFFER_SIZE)
		{
			len = read(fd, temp, BUFFER_SIZE);
			temp[len] = '\0';
			if (temp[0])
				doc = linejoin(doc, temp, len);
		}
		if (len == 0)
			*flag = 1;
		temp = free_n_null(temp);
		return (doc);
	}
	temp = free_n_null(temp);
	return (doc);
}

static char	*take_first_line(char *doc)
{
	char	*line;
	int		i;

	i = 0;
	while (doc[i] && (i == 0 || doc[i - 1] != '\n'))
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (line && doc && doc[0])
	{
		i = 0;
		while (doc[i] && (i == 0 || doc[i - 1] != '\n'))
		{
			line[i] = doc[i];
			i++;
		}
		line[i] = '\0';
		doc = remove_line(doc, line);
		return (line);
	}
	line = free_n_null(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*docs[OPEN_MAX];
	char		*line;
	int			flag;

	flag = 0;
	line = NULL;
	if (fd >= 0 && read(fd, 0, 0) >= 0 && BUFFER_SIZE > 0)
	{
		if (!docs[fd])
			docs[fd] = create_doc();
		if (!has_line(docs[fd]))
			docs[fd] = read_next_line(fd, docs[fd], &flag);
		if (docs[fd][0])
			line = take_first_line(docs[fd]);
		if (flag)
			docs[fd] = free_n_null(docs[fd]);
		return (line);
	}
	line = free_n_null(line);
	return (NULL);
}
