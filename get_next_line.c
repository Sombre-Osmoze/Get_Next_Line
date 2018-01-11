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

static int	ft_stock_data(int fd, char *rest, t_ctrl *ctrl, size_t size)
{
	size_t	*ref;

	ref = NULL;
	if (*rest != '\0' && size != 0)
		ref = ft_memalloc(sizeof(size_t) * 2);
	if (ref && ft_create_item(ctrl, ctrl->nb_item) != NULL)
	{
		ref[0] = fd;
		ref[1] = 0;
		ctrl->last_ac->content_ref = ref;
		ctrl->last_ac->content = ft_memjoin(rest, size, NULL, 0);
		ctrl->last_ac->content_size = size;
		return (1);
	}
	return (1);
}

static int	ft_read_line(const int fd, char **line, t_ctrl *ctrl, size_t res)
{
	char			tmp[BUFF_SIZE + 1];
	size_t			i[3];
	char			*buff;

	ft_bzero(i, sizeof(i));
	i[1] = BUFF_SIZE + 1;
	while (i[1] == BUFF_SIZE + 1 && (i[0] = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		i[1] = ft_memichr(tmp, '\n', BUFF_SIZE);
		if (i[1] == BUFF_SIZE + 1)
			buff = ft_strnjoin(*line, res, tmp, i[0]);
		else
			buff = ft_strnjoin(*line, res, tmp, i[1]);
		if (*line)
			free(*line);
		*line = buff;
		if (i[1] != BUFF_SIZE + 1)
			res += i[1];
		else
			res += i[0];
		i[2] = i[0];
	}
	if (i[1] < i[2])
		return (ft_stock_data(fd, &tmp[i[1] + 1], ctrl, i[2] - (i[1] + 1)));
	return ((int)i[2]);
}

static int	ft_get_buff(const int fd, char **line, t_ctrl *cl, int *rest)
{
	size_t	lim;
	size_t	*ref;

	lim = 0;
	if (cl && ft_search_item(cl, (const void *)&fd, 0, &ft_int_cmp))
	{
		ref = (size_t *)cl->last_ac->content_ref;
		lim = ft_memichr(((char *)(cl->last_ac->content)) + ref[1], '\n',
									cl->last_ac->content_size - ref[1]);
		if (lim != cl->last_ac->content_size + 1 - ref[1])
		{
			*rest = 42;
			*line = ft_strnjoin(NULL, 0,
								((char *)cl->last_ac->content) + ref[1], lim);
			ref[1] += lim + 1;
		}
		else
			*line = ft_strnjoin(NULL, 0,
							((char *)cl->last_ac->content), lim - 1 - ref[1]);
		if (lim == cl->last_ac->content_size + 1 - ref[1]
				|| ref[1] >= cl->last_ac->content_size)
			ft_rm_item(cl, cl->last_ac->row);
	}
	return ((int)lim);
}

/*
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
	if (fd > -1 && BUFF_SIZE > 0 && line)
	{
		if (!ctrl)
			ctrl = ft_init_ctrl();
		*line = NULL;
		res[1] = ft_get_buff(fd, line, ctrl, res);
		if (res[0] != 42)
			res[0] = ft_read_line(fd, line, ctrl, res[1]);
		if (res[0] == 0 && !line)
			res[0] = 1;
		if (res[0] == -1)
			ft_rm_list(ctrl);
	}
	else
		res[0] = -1;
	if (res[0])
		res[0] = 1;
	return (res[0]);
}
