/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:45:47 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/16 23:45:51 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*buff;
	size_t	i[2];

	buff = NULL;
	i[0] = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && buff == NULL && i[0] < len)
	{
		if (*haystack == *needle && (i[0] + ft_strlen(needle) - 1) < len)
		{
			buff = (char *)haystack;
			i[1] = 0;
			while (needle[i[1]] != '\0' && buff != NULL)
			{
				if (buff[i[1]] != needle[i[1]])
					buff = NULL;
				else
					i[1]++;
			}
		}
		haystack++;
		i[0]++;
	}
	return (buff);
}
