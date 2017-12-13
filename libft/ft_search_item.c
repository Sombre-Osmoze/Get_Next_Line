/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_item.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:43:00 by mflorent          #+#    #+#             */
/*   Updated: 2017/04/12 09:43:00 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_item	*ft_search_item(t_ctrl *ctrl, const void *ref, int i,
						int (*cmp)(const void *cmp, const void *ref, int i))
{
	t_item	*tmp;

	tmp = ctrl->head;
	while (tmp != NULL)
	{
		if ((cmp)(tmp->content_ref, ref, i))
		{
			ctrl->last_ac = tmp;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}
