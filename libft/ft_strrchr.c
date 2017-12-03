/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 19:40:36 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/16 19:40:43 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*buf;

	buf = NULL;
	while (*s != '\0')
	{
		if (*s == c)
			buf = (char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (buf);
}
