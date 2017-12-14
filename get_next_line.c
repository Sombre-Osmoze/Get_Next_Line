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

static void	ft_stock_data(int fd, char *rest, t_ctrl *ctrl, size_t end)
{
	int	*ref;

	ref = ft_memalloc(sizeof(int) * 2);
	if (ft_create_item(ctrl, ctrl->nb_item) != NULL && ref != NULL)
	{
		ref[0] = fd;
		ref[1] = 0;
		ctrl->last_ac->content_ref = ref;
		ctrl->last_ac->content = ft_memjoin(rest, end, NULL, 0);
		ctrl->last_ac->content_size = end;
	}
}

static int	ft_read_line(const int fd, char **line, t_ctrl *ctrl, size_t res[2])
{
	char			tmp[BUFF_SIZE + 1];
	size_t			i[4];
	char			*buff;

	ft_bzero(i, sizeof(i));
	buff = NULL;
	i[2] = res[1];
	i[1] = BUFF_SIZE + 1;
	while (i[1] == BUFF_SIZE + 1 && (i[0] = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		i[1] = ft_memichr(tmp, '\n', BUFF_SIZE);
		if (i[1] == BUFF_SIZE + 1)
			buff = ft_strnjoin(*line, i[2], tmp, i[0]);
		else
			buff = ft_strnjoin(*line, i[2], tmp, i[1]);
		if (*line)
			free (*line);
		*line = buff;
		i[2] += i[0];
		i[3] = i[0];
	}
	if (i[2] != 0 && i[1] != BUFF_SIZE + 1 && i[1] < i[3])
		ft_stock_data(fd, tmp + i[1] + 1, ctrl, BUFF_SIZE - i[1] - 1);
	if (i[0] || i[1] < i[3])
		i[0] = 1;
	return ((int)i[0]);
}

static char	*ft_get_buff(const int fd, char **line, t_ctrl *ctrl, size_t res[2])
{
	size_t	lim;
	int		*ref;

	lim = 0;
	if (ctrl && ft_search_item(ctrl, (const void *)&fd, 0,  &ft_int_cmp))
	{
		ref = (int *)ctrl->last_ac->content_ref;
		lim = ft_memichr((char *)(ctrl->last_ac->content) + ref[1], '\n',
						 ctrl->last_ac->content_size);
		if (lim != ctrl->last_ac->content_size + 1)
		{
			res[1] = lim;
			res[0] = 42;
		}
		else
			lim--;
		ref[1] = (int)lim;
		*line = (char *)ft_memjoin(NULL, 0, ctrl->last_ac->content, lim);
//		if (lim == ctrl->last_ac->content_size)
//			ft_rm_item(ctrl, ctrl->last_ac->row);
	}
	return (*line);
}

int			get_next_line(const int fd, char **line)
{
	static t_ctrl	*ctrl;
	size_t			res[2];

	ft_bzero(res, sizeof(res));
	if (!ctrl)
		ctrl = (t_ctrl *)ft_init_ctrl();
	if (fd > 0)
	{
		*line = NULL;
		*line = ft_get_buff(fd, line, ctrl, res);
		if (res[0] != (size_t)42)
			res[0] = ft_read_line(fd, line, ctrl, res);
	}
	else
		res[0] = fd;
	return ((int)res[0]);
}
