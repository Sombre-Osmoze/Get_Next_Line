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
	static t_ctrl *data_ctrl;
	int res;
	if (fd > 0)
	{
	if (line != NULL)
	{
		free(*line);
		line = NULL;
	}
		line = malloc(sizeof(char *));
		res = ft_read_line(fd, line, data_ctrl);
	}
	else
		res = fd;

	return (res);
}

static int	ft_read_line(const int fd, char **line, t_ctrl *data_ctrl)
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
	if (i[0] < BUFF_SIZE)
	{
		ft_stock_data(fd, tmp, data_ctrl, BUFF_SIZE - i[0]);
	}
	free(tmp);
	return (i[2]);
}

static void	ft_stock_data(const int fd, char *rest, t_ctrl *data_ctrl, int end)
{
	if (ft_create_item(data_ctrl, data_ctrl->last->row + 1) != NULL) {
		data_ctrl->curr->content_ref = fd;
		data_ctrl->curr->content = malloc(sizeof(char));
		memcpy(data_ctrl->curr->content, rest, end);
	}


}
