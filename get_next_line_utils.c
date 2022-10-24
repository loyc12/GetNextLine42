/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:26:51 by llord             #+#    #+#             */
/*   Updated: 2022/06/13 13:57:35 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_n_null(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

char	*create_doc(void)
{
	char	*doc;

	doc = malloc(1 * sizeof(char));
	doc[0] = '\0';
	return (doc);
}

static size_t	find_lenght(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*linejoin(char *s1, char *s2, int len)
{
	int		i;
	int		offset;
	char	*str;

	str = malloc((find_lenght(s1) + len + 1) * sizeof(char));
	str[0] = '\0';
	if (str)
	{
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		s1 = free_n_null(s1);
		offset = i;
		i = -1;
		while (s2[++i] && i < len)
			str[offset + i] = s2[i];
		str[i + offset] = '\0';
		return (str);
	}
	s1 = free_n_null(s1);
	return (s1);
}

char	*remove_line(char *doc, char *line)
{
	int		offset;
	int		i;

	offset = find_lenght(line);
	i = find_lenght(doc);
	if (doc && doc[0] && (1 + i - offset) > 0)
	{
		i = -1;
		while (doc[++i + offset])
			doc[i] = doc[i + offset];
		doc[i] = '\0';
		if (i != 0)
			return (doc);
	}
	return (doc);
}
