/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:29:09 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/23 15:29:10 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*item;

	new_lst = NULL;
	if (lst != NULL && (f) != NULL)
	{
		item = (f)(lst);
		new_lst = item;
		lst = lst->next;
		while (lst != NULL)
		{
			item->next = (*f)(lst);
			item = item->next;
			lst = lst->next;
		}
	}
	return (new_lst);
}
