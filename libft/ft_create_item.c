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

t_item	*ft_create_item(t_ctrl *ctrl, int pos)
{
	t_item	*tmp;
	t_item	*new_item;

	new_item = NULL;
	tmp = ctrl->first;
	while (tmp->row < pos - 1)
		tmp = tmp->next;
	if ((new_item = malloc(sizeof(t_item))) != NULL)
	{
		new_item->content = NULL;
		new_item->content_ref = 0;
		new_item->row = new_item->next->row;
		new_item->prev = tmp;
		new_item->next = tmp->next;
		new_item->ctrl = ctrl;
		ctrl->curr = new_item;
		tmp->next = new_item;
		tmp = new_item->next;
		while (tmp != NULL)
		{
			tmp->row = tmp->row + 1;
			tmp = tmp->next;
		}
	}
	return (new_item);
}
