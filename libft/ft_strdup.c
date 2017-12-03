/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:25:34 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/16 12:25:35 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = NULL;
	while (s1[i] != '\0')
		i++;
	cpy = malloc(sizeof(char) * i + 1);
	if (cpy != NULL)
	{
		i = 0;
		while (s1[i] != '\0')
		{
			cpy[i] = s1[i];
			i++;
		}
		cpy[i] = '\0';
	}
	return (cpy);
}
