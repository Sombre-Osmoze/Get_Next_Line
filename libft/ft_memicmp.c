/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memicmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:55:43 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/22 13:55:45 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_memicmp(const void *s1, const void *s2, size_t len)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	size_t			i;

	i = 0;
	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	while (i < len)
	{
		if (p_s1[i] != p_s2[i])
			return (i);
		i++;
	}
	return (len);
}
