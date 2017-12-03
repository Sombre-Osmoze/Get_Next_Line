/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:18:52 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/15 17:10:17 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	int				find;
	unsigned char	*src_p;
	unsigned char	*dst_p;

	i = 0;
	find = 0;
	src_p = (unsigned char *)src;
	dst_p = dst;
	while (i < n && !find)
	{
		if (src_p[i] == (unsigned char)c)
			find = 1;
		*dst_p++ = (unsigned char)src_p[i];
		i++;
	}
	if (!find)
		return (NULL);
	return (dst_p);
}
