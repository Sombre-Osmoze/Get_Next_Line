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

	ref = 0;
	if (*rest != '\0' && end != 0)
		ref = ft_memalloc(sizeof(int) * 2);
	if (ref && *rest != 0 && end && ft_create_item(ctrl, ctrl->nb_item) != NULL)
	{
		ref[0] = fd;
		ref[1] = 0;
		ctrl->last_ac->content_ref = ref;
		ctrl->last_ac->content = ft_memjoin(rest, end, NULL, 0);
		ctrl->last_ac->content_size = end;
	}
}

static int	ft_read_line(const int fd, char **line, t_ctrl *ctrl, size_t res)
{
	char			tmp[BUFF_SIZE + 1];
	size_t			i[4];
	char			*buff;

	ft_bzero(i, sizeof(i));
	buff = NULL;
	i[2] = res;
	i[1] = BUFF_SIZE + 1;
	while (i[1] == BUFF_SIZE + 1 && (i[0] = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		i[1] = ft_memichr(tmp, '\n', BUFF_SIZE);
		if (i[1] == BUFF_SIZE + 1)
			buff = ft_strnjoin(*line, i[2], tmp, i[0]);
		else
			buff = ft_strnjoin(*line, i[2], tmp, i[1]);
		if (*line)
			free(*line);
		*line = buff;
		if (i[1] != BUFF_SIZE + 1)
			i[2] += i[1];
		else
			i[2] += i[0];
		i[3] = i[0];
	}
	if (i[1] < BUFF_SIZE)
		ft_stock_data(fd, &tmp[i[1] + 1], ctrl, BUFF_SIZE - i[1] - 1);
	if (i[0] && i[3] != 1)
		return (1);
	return ((int)i[3]);
}

static int	ft_get_buff(const int fd, char **line, t_ctrl *cl, int *rest)
{
	size_t	lim;
	int		*ref;

	lim = 0;
	if (cl && ft_search_item(cl, (const void *)&fd, 0, &ft_int_cmp))
	{
		ref = (int *)cl->last_ac->content_ref;
		lim = ft_memichr((char *)(cl->last_ac->content) + ref[1], '\n',
									cl->last_ac->content_size);
		if (lim == cl->last_ac->content_size + 1)
			lim = (size_t)cl->last_ac->content_size;
		else
		{
			*rest = 42;
			ref[1] = (int)lim + 1;
		}
		*line = ft_strnjoin(NULL, 0, cl->last_ac->content, lim++);
		if (lim == cl->last_ac->content_size + 1)
			ft_rm_item(cl, cl->last_ac->row);
	}
	return ((int)lim);
}

/**
** Renvoie un fichier ligne par ligne dans un tableau de 'char' alloué
** @param fd File descriptor -> "open()"
** @param line Le tableau de 'char' contenant la ligne actuelle
** @return Information sur le fichier
*/

int			get_next_line(const int fd, char **line)
{
	static t_ctrl	*ctrl;
	int				res[2];

	ft_bzero(res, sizeof(res));
	if (fd > 0)
	{
		if (!ctrl)
			ctrl = (t_ctrl *)ft_init_ctrl();
		*line = NULL;
		res[1] = ft_get_buff(fd, line, ctrl, res);
		if (res[0] != 42)
			res[0] = ft_read_line(fd, line, ctrl, res[1]);
		if (res[0] ==  -1 || res[0] == 0)
			ft_rm_list(ctrl);
	}
	else
		res[0] = fd;
	return (res[0]);
}
