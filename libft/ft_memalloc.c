/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:28:20 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/18 18:28:25 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*new_buff;
	char	*set_buff;
	size_t	i;

	new_buff = NULL;
	i = 0;
	new_buff = malloc(size);
	if (new_buff != NULL)
	{
		set_buff = new_buff;
		while (i < size)
			set_buff[i++] = '\0';
	}
	return (new_buff);
}
