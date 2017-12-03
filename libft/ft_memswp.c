/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 22:01:04 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/21 22:01:06 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_memswp(void *a, void *b, size_t len)
{
	size_t			i;
	unsigned char	tmp;
	unsigned char	*a_p;
	unsigned char	*b_p;

	i = 0;
	a_p = (unsigned char *)a;
	b_p = (unsigned char *)b;
	while (i < len)
	{
		tmp = *a_p;
		*a_p = *b_p;
		*b_p = tmp;
		i++;
	}
}
