/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:18:27 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/23 16:55:06 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str1;
	char	*str2;

	str1 = (char *)dst;
	str2 = (char *)src;
	if (len == 0)
		return (dst);
	if (str2 < str1)
	{
		str1 = str1 + len - 1;
		str2 = str2 + len - 1;
		while (len-- > 0)
			*str1-- = *str2--;
	}
	else
	{
		while (len > 0)
		{
			*str1++ = *str2++;
			len--;
		}
	}
	return (dst);
}
