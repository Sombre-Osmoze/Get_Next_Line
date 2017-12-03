/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 19:59:44 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/22 23:41:39 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*buff;
	size_t	i;

	buff = NULL;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && buff == NULL)
	{
		if (*haystack == *needle)
		{
			buff = (char *)haystack;
			i = 0;
			while (needle[i] != '\0' && buff != NULL)
				if (buff[i] != needle[i])
					buff = NULL;
				else
					i++;
		}
		haystack++;
	}
	return (buff);
}
