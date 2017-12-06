/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 04/12/2017 10:12:00 by mflorent          #+#    #+#             */
/*   Updated: 04/12/2017 10:12:00 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_item	*ft_get_item(t_ctrl *ctrl, int pos)
{
	t_item	*tmp;

	tmp = ctrl->first;
	while (tmp != NULL)
	{
		if (tmp->row == pos)
		{
			ctrl->curr = tmp;
			return (tmp);
		}
	}
	return (tmp);
}
