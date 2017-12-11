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
	static t_ctrl	*ctrl;
	int				res;
	if (fd > 0)
	{
		if (ft_search_item(ctrl, (const void *)&fd, &ft_int_cmp))
			*line = ft_memjoin(NULL, 0, ctrl->last_ac->content,
							   ctrl->last_ac->content_size);
		res = ft_read_line(fd, NULL, ctrl);
	}
	else
		res = fd;

	return (res);
}

static int	ft_read_line(const int fd, char *line, t_ctrl *data_ctrl)
{
	char			tmp[BUFF_SIZE];
	size_t			i[3];

	ft_bzero(i, 3);
	i[1] = 1;
	while ((i[0] = read(fd, tmp, BUFF_SIZE)) > 0 && i[1])
	{
		i[2] = ft_memicmp(tmp, "\n", BUFF_SIZE);
		
		
		
		
		
	}
	if (i[0] && i[2] < BUFF_SIZE)
	{
		ft_stock_data(fd, tmp, data_ctrl, BUFF_SIZE - i[0]);
	}
	return ((int)i[2]);
}

static void	ft_stock_data(const int fd, char *rest, t_ctrl *ctrl, size_t end)
{
	if (ft_create_item(ctrl, ctrl->tail->row + 1) != NULL) {
		ctrl->last_ac->content_ref = fd;
		ctrl->last_ac->content = ft_memjoin(rest, end, NULL, 0);
		ctrl->last_ac->content_size = end;
	}


}
