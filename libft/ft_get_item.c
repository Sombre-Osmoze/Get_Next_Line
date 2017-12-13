/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:12:00 by mflorent          #+#    #+#             */
/*   Updated: 2017/04/12 10:12:00 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

t_item	*ft_get_item(t_ctrl *ctrl, size_t pos)
{
	t_item	*tmp;

	tmp = ctrl->head;
	while (tmp != NULL)
	{
		if (tmp->row == pos)
		{
			ctrl->last_ac = tmp;
			return (tmp);
		}
	}
	return (tmp);
}
