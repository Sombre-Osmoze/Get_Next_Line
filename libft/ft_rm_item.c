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

t_item	*ft_rm_item(t_ctrl *ctrl, int pos)
{
	t_item	*tmp;

	tmp = ft_get_item(ctrl, pos);
	if (tmp != NULL)
	{
		free(tmp->content);
		tmp->content = NULL;
		tmp->row = -1;
		tmp->content_ref = -1;
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		ctrl->curr = tmp->next;
		tmp->ctrl = NULL;
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		ctrl->nbItem = ctrl->nbItem - 1;
		tmp = ctrl->curr;
		while (tmp != NULL)
		{
			tmp->row = tmp->row - 1;
			tmp = tmp->next;
		}
	}
	return (tmp);
}
