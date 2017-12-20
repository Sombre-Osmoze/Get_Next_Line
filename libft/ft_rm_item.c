/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_item.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:08:00 by mflorent          #+#    #+#             */
/*   Updated: 2017/04/12 10:08:00 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_delete_data(t_ctrl *ctrl, t_item *tmp)
{
	if (tmp->content)
		free(tmp->content);
	if (tmp->content_ref)
		free(tmp->content_ref);
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (ctrl->head == tmp)
		ctrl->head = NULL;
	if (ctrl->tail == tmp)
		ctrl->tail = NULL;
	if (ctrl->curr == tmp)
		ctrl->curr = NULL;
	ctrl->last_ac = tmp->next;
}

t_item		*ft_rm_item(t_ctrl *ctrl, size_t pos)
{
	t_item	*tmp;

	tmp = ft_get_item(ctrl, pos);
	if (tmp != NULL)
	{
		ft_delete_data(ctrl, tmp);
		tmp->content = NULL;
		tmp->row = -1;
		tmp->ctrl = NULL;
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		ctrl->nb_item = ctrl->nb_item - 1;
		tmp = ctrl->last_ac;
		while (tmp != NULL)
		{
			tmp->row = tmp->row - 1;
			tmp = tmp->next;
		}
		ctrl->last_ac = tmp;
	}
	return (tmp);
}
