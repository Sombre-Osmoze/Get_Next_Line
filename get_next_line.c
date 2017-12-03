/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 04:16:39 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/28 04:16:44 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_next_line(const int fd, char **line)
{
	static char **fd_data;
	int res;
	if (fd > 0)
	{
	if (line != NULL)
	{
		free(*line);
		line = NULL;
	}
		line = malloc(sizeof(char *));
		res = ft_read_line(fd, line, fd_data);
	}
	else
		res = fd;

	return (res);
}

static int	ft_read_line(const int fd, char **line, char *data[])
{
	char			tmp[BUFF_SIZE];
	int	i[3];

	i[0] = 1;
	while (i[0] < 3)
		i[i[0]++] = 0;
	while (tmp[i[0]] != '\n')
	{
		read(fd, tmp, BUFF_SIZE);
		*line = malloc(sizeof(char) * i[0] * BUFF_SIZE);

	}

	return (i[2]);
}

static void	ft_stock_data(const int fd, char *rest, char *data[])
{
	int	i[2];

	i[0] = 0;
	while (data[i[0]][0] != -42)
		i[0]++;
	data[i[0]] = ft_strnew(ft_strlen(rest) + ft_strlen(ft_itoa(fd)) + 1 );
	data[i[0]++][0] = 1;
	ft_strcpy(data[i[0]++] + 1, ft_itoa(fd));
	data[i[0]++][0] = 2;
	


}
