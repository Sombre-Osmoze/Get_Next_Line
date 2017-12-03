/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:17:40 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/15 11:17:43 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			c;
	unsigned char	*src_p;
	unsigned char	*dst_p;

	c = 0;
	src_p = (unsigned char *)src;
	dst_p = dst;
	while (c < n)
	{
		dst_p[c] = src_p[c];
		c++;
	}
	return (dst);
}
