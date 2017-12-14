/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_item.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 00:05:00 by mflorent          #+#    #+#             */
/*   Updated: 2017/04/12 00:05:00 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <string.h>

static void		ft_set_null(t_ctrl *ctrl, t_item *new, size_t pos)
{
	new->content = NULL;
	new->content_ref = 0;
	new->content_size = 0;
	new->row = pos;
	new->ctrl = ctrl;
	new->next = NULL;
	new->prev = NULL;
	ctrl->last_ac = new;
	ctrl->nb_item += +1;
}

static t_item	*ft_spc_creat(t_ctrl *ctrl, size_t pos)
{
	t_item	*new_item;

	new_item = malloc(sizeof(t_item));
	if (new_item)
	{
		ft_set_null(ctrl, new_item, pos);
		if (ctrl->head)
		{
			new_item->next = ctrl->head;
			ctrl->head->prev = new_item;
		}
		else if (ctrl->nb_item - 1 == 0)
			ctrl->tail = new_item;
		ctrl->head = new_item;
	}
	return (new_item);
}

static t_item	*ft_mv_prev_pos(t_ctrl *c, unsigned long long res[4], size_t ps)
{
	unsigned long long	tmp;
	int					i[2];

	tmp = res[0];
	if (c->nb_item <= 15)
		return (c->head);
	ft_bzero(i, sizeof(i[0] * 2));
	while (i[0] < 4)
	{
		if (res[i[0]] < tmp)
		{
			tmp = res[i[0]];
			i[1]++;
		}
	}
	if (c->head && (i[1] == 0 || c->head->row == ps - 1))
		return (c->head);
	if (c->tail && (i[1] == 1 || c->tail->row == ps - 1))
		return (c->tail);
	if (c->curr && (i[1] == 2 || c->curr->row == ps - 1))
		return (c->curr);
	if (c->last_ac && (i[1] == 3 || c->last_ac->row <= ps - 1))
		return (c->last_ac);
	return (NULL);
}

static t_item	*ft_get_way(t_ctrl *ctrl, size_t pos)
{
	unsigned long long	res[4];
	t_item				*tmp;

	ft_bzero(res, sizeof(res[0] * 5));
	if (pos == 0)
		return (NULL);
	if (ctrl->head)
		res[0] = ft_abs(ctrl->head->row - pos);
	if (ctrl->tail)
		res[1] = ft_abs(ctrl->tail->row - pos);
	if (ctrl->curr && ctrl->curr != ctrl->head && ctrl->curr != ctrl->tail)
		res[2] = ft_abs(ctrl->curr->row - pos);
	if (ctrl->last_ac && ctrl->curr != ctrl->head && ctrl->curr != ctrl->tail
			&& ctrl->curr != ctrl->curr)
		res[3] = ft_abs(ctrl->last_ac->row - pos);
	tmp = ft_mv_prev_pos(ctrl, res, pos);
	if (tmp && tmp->row == pos - 1 && tmp->row - pos > 0)
		while (tmp && tmp->row == pos - 1)
			tmp = tmp->next;
	else if (tmp && tmp->row == pos - 1 && (long long)(tmp->row - pos) < 0)
		while (tmp && tmp->row == pos - 1)
			tmp = tmp->prev;
	return (tmp);
}

/*
**  Fontion wich create a new item (t_item) of a list pour une position > 0.
**	@param ctrl The pointer to a controler "t_ctrl" of a list of "t_item.
**	@param pos The position where the item must be created.
**	@return The poiter to the new item "t_item".
*/

t_item			*ft_create_item(t_ctrl *ctrl, size_t pos)
{
	t_item	*tmp;
	t_item	*new_item;

	if (!ctrl)
		return (NULL);
	if (pos == 0)
		new_item = ft_spc_creat(ctrl, pos);
	else
	{
		tmp = ft_get_way(ctrl, pos);
		if (tmp == NULL || (new_item = malloc(sizeof(t_item))) == NULL)
			return (NULL);
		ft_set_null(ctrl, new_item, pos);
		new_item->prev = tmp;
		new_item->next = tmp->next;
		tmp->next = new_item;
	}
	tmp = new_item->next;
	while (tmp != NULL)
	{
		tmp->row = tmp->row + 1;
		tmp = tmp->next;
	}
	return (new_item);
}
