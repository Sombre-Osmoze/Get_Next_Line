/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 21:41:12 by mflorent          #+#    #+#             */
/*   Updated: 2017/12/13 17:20:02 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*fill(char *buff, int i)
{
	while (buff[i])
	{
		buff[i] = '\0';
		i += 1;
	}
	return (buff);
}

static char		*passe(char *buffer, int j)
{
	int			i;

	i = 0;
	while (buffer[i] && buffer[j])
		buffer[i++] = buffer[j++];
	buffer = fill(buffer, i);
	return (buffer);
}

static int		len(char *buffer, char *b_lines)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (b_lines && b_lines[j])
		j++;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	return (i + j);
}

static char		*ft_realloc(char *b_lines, char *buffer, int *var)
{
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (len(buffer, b_lines)) + 1)))
		return (NULL);
	while (b_lines && b_lines[i])
	{
		tmp[i] = b_lines[i];
		i++;
	}
	while (buffer[j] && buffer[j] != '\n')
		tmp[i++] = buffer[j++];
	tmp[i] = '\0';
	if (buffer[j] == '\n')
		*var = 1;
	j++;
	buffer = passe(buffer, j);
	free(b_lines);
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	static char	buffer[12288][BUFF_SIZE + 1];
	int			ret;
	int			var;

	ret = -1;
	var = 0;
	if (fd < 0 || !line || fd > 12287)
		return (-1);
	if ((*line = ft_realloc(NULL, buffer[fd], &var)) == NULL)
		return (-1);
	while (ret != 0 && var == 0)
	{
		if ((ret = read(fd, buffer[fd], BUFF_SIZE)) < 0
			|| (*line = ft_realloc(*line, buffer[fd], &var)) == NULL)
			return (-1);
	}
	if (ret == 0 && *line[0] == '\0')
		return (0);
	return (1);
}
