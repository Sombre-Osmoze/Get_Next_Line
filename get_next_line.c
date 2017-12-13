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
	if (ft_create_item(ctrl, ctrl->tail->row + 1) != NULL) {
		ref[0] = fd;
		ref[1] = 0;
		ctrl->last_ac->content_ref = ref;
		ctrl->last_ac->content = ft_memjoin(rest, end, NULL, 0);
		ctrl->last_ac->content_size = end;
	}


}

static int	ft_read_line(const int fd, char **line, t_ctrl *data_ctrl)
{
	char			tmp[BUFF_SIZE];
	size_t			i[3];

	ft_bzero(i, 3);
	i[1] = 1;
	while ((i[0] = read(fd, tmp, BUFF_SIZE)) > 0 && i[1])
	{
		i[2] = ft_memichr(tmp, '\n', BUFF_SIZE);





	}
	if (i[2] < BUFF_SIZE)
	{
		ft_stock_data(fd, &tmp[i[2]], data_ctrl, BUFF_SIZE - i[0]);
	}
	return ((int)i[2]);
}

static char	**ft_get_buff(const int fd, char **line, t_ctrl *ctrl, int *res)
{
	size_t	lim;
	int		*ref;

	if (ctrl && ft_search_item(ctrl, (const void *)&fd, 0,  &ft_int_cmp))
	{
		ref = (int *)ctrl->last_ac->content_ref;
		lim = ft_memichr(ctrl->last_ac->content, '\n',
						 ctrl->last_ac->content_size);
		if (lim != (size_t)-1)
		{
			lim = ctrl->last_ac->content_size;
			*res = 3;
			ref[1] = (int)lim;
		}
		*line = (char *)ft_memjoin(NULL, 0, ctrl->last_ac->content, lim);
		if (lim == (size_t)-1)
			ft_rm_item(ctrl, ctrl->last_ac->row);
	}
	return (line);
}

int			get_next_line(const int fd, char **line)
{
	static t_ctrl	*ctrl;
	int				res;

	res = 0;
	if (!ctrl)
		ctrl = (t_ctrl *)ft_init_ctrl();
	if (fd > 0)
	{
		line = ft_get_buff(fd, line, ctrl, &res);
		if (res != 3)
			res = ft_read_line(fd, line, ctrl);
	}
	else
		res = fd;




	return (res);
}
