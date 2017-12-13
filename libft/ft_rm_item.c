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

t_item	*ft_rm_item(t_ctrl *ctrl, size_t pos)
{
	t_item	*tmp;

	tmp = ft_get_item(ctrl, pos);
	if (tmp != NULL)
	{
		free(tmp->content);
		free(tmp->content_ref);
		tmp->content = NULL;
		tmp->row = -1;
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		ctrl->last_ac = tmp->next;
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
	}
	return (tmp);
}
