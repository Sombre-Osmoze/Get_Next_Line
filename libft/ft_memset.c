/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:22:47 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/14 20:28:50 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*b_p;

	b_p = b;
	i = 0;
	while (i < len)
		b_p[i++] = (unsigned char)c;
	return (b);
}
