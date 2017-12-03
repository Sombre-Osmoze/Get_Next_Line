/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:20:54 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/20 10:20:55 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;

	new_str = NULL;
	if (s != NULL && (f) != NULL)
	{
		i = 0;
		while (s[i] != '\0')
			i++;
		new_str = malloc(sizeof(char) * i + 1);
		i = 0;
		if (new_str != NULL)
		{
			while (s[i] != '\0')
			{
				new_str[i] = (f)(i, s[i]);
				i++;
			}
			new_str[i] = '\0';
		}
	}
	return (new_str);
}
