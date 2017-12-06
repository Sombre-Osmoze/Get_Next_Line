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

////////
#include <stdio.h>
////////

int			get_next_line(const int fd, char **line)
{
	static t_ctrl	*data_ctrl;
	int				res;
	if (fd > 0)
	{
		res = ft_read_line(fd, NULL, data_ctrl);
	}
	else
		res = fd;

	return (res);
}

static int	ft_read_line(const int fd, char *line, t_ctrl *data_ctrl)
{
	char			tmp[BUFF_SIZE];
	int				i[3];

	i[0] = 1;
	while (i[0] < 3)
		i[i[0]++] = 0;
//	line = ft_get_buff(fd, line, data_ctrl);
	while (read(fd, tmp, BUFF_SIZE))
	{

		/////
		printf("%s", tmp);
		/////
	}
//	if (i[0] < BUFF_SIZE)
//	{
//		ft_stock_data(fd, tmp, data_ctrl, BUFF_SIZE - i[0]);
//	}
	return (i[2]);
}

static void	ft_stock_data(const int fd, char *rest, t_ctrl *data_ctrl, int end)
{
	if (ft_create_item(data_ctrl, data_ctrl->last->row + 1) != NULL) {
		data_ctrl->curr->content_ref = fd;
		data_ctrl->curr->content = malloc(sizeof(char));
		data_ctrl->curr->content_size = end;
		memcpy(data_ctrl->curr->content, rest, end);

	}


}

static char	*ft_get_buff(const int fd, char *line, t_ctrl *data_ctrl)
{
	if (ft_search_item(data_ctrl, fd) != NULL)
	{
		line = malloc(sizeof(char) * data_ctrl->curr->content_size + 1);
		

	}


	return (line);
}
