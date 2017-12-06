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

t_item	*ft_search_item(t_ctrl *ctrl, const int ref)
{
	t_item	*tmp;

	tmp = ctrl->first;
	while (tmp != NULL)
	{
		if (tmp->content_ref == ref)
		{
			ctrl->curr = tmp;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}
