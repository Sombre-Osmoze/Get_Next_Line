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
#include <string.h>
#include "libft.h"

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
	ctrl->nb_item += 1;
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
		tmp = ft_get_item(ctrl, pos - 1);
		if (tmp == NULL || (new_item = malloc(sizeof(t_item))) == NULL)
			return (NULL);
		ft_set_null(ctrl, new_item, pos);
		new_item->prev = tmp;
		if (tmp)
		{
			new_item->next = tmp->next;
			tmp->next = new_item;
		}
	}
	tmp = new_item->next;
	while (tmp != NULL)
	{
		tmp->row = tmp->row + 1;
		tmp = tmp->next;
	}
	return (new_item);
}
