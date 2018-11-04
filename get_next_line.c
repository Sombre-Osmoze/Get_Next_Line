/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 04:16:39 by mflorent          #+#    #+#             */
/*   Updated: 2017/11/28 04:16:44 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static long	ft_stock_data(int fd, char *rest, t_ctrl **ctrl, long i[3])
{
	size_t	*ref;

	ref = NULL;
	if (*rest && i[0] - i[1] != 0)
		ref = ft_memalloc(sizeof(size_t) * 2);
	else
		return (i[2]);
	if (ref && ft_create_item(ctrl, (*ctrl)->count) != NULL)
	{
		ref[0] = fd;
		(*ctrl)->last_ac->content_ref = ref;
		(*ctrl)->last_ac->content = ft_memndup(rest, (size_t)i[0] - i[1] - 1);
		(*ctrl)->last_ac->content_size = i[0] - i[1] - 1;
		return (i[2]);
	}
	return (-1);
}
#include <stdio.h>
static long	ft_read_line(const int fd, char **line, t_ctrl **ctrl, long lg)
{
	long			i[3];
	char			tmp[BUFF_SIZE + 1];
	char			*buff;

	if (lg == -1 || !ctrl || !*ctrl)
		return (0);
	ft_longset(i, 0, 3);
	i[1] = -1;
	i[2] = lg;
	while (i[1] == -1 && (i[0] = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		i[1] = (long)ft_memichr(tmp, '\n', i[0]);
		buff = ft_strnjoin(*line, i[2], tmp, i[1] == -1 ? *i : i[1]);
		if (*line)
			free(*line);
		*line = buff;
		i[2] += i[1] != -1 ? i[1] + 1 : i[0];
		if (i[1] != -1 && i[1] + 1 != BUFF_SIZE)
			return (ft_stock_data(fd, &tmp[i[1] + 1], ctrl, i));
	}
	return ((*line && i[2]) ? i[2] : i[0]);
}

static long	ft_get_buff(const int *fd, char **line, t_ctrl *cl, long *rest)
{
	size_t	lim;
	size_t	*ref;
	size_t	size;
	char	*content;

	if (BUFF_SIZE > 1 && cl && ft_search_item(cl, fd, 0, &ft_item_ref))
	{
		ref = (size_t *)cl->last_ac->content_ref;
		content = (char *)cl->last_ac->content + ref[1];
		size = cl->last_ac->content_size - ref[1];
		lim = ft_memichr(content, '\n', size);
		*line = ft_strndup(content, lim != (size_t)-1 ? lim : size);
		ref[1] += lim + 1;
		if (lim == (size_t)-1 || lim + 1 >= size)
			ft_rm_item(cl, cl->last_ac->row);
		if (lim == (size_t)-1)
			*rest = size;
		else
			*rest = -1;
		return (*rest == -1 ? lim + 1 : 0);
	}
	return (0);
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
	long			res;

	res = 0;
	if (fd > -1 && BUFF_SIZE >= 0 && line)
	{
		if (ctrl == NULL)
			ctrl = ft_init_ctrl();
		*line = NULL;
		res = ((int)(ft_get_buff(&fd, line, ctrl, &res) | ft_read_line(fd, line, &ctrl, res)));
		if (res >= 1)
			return (1);
		else 
			return ((int)res);
	}
	return (-1);
}
