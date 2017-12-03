/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:09:44 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/20 10:09:51 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*new_str;
	int		i;

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
				new_str[i] = (f)(s[i]);
				i++;
			}
			new_str[i] = '\0';
		}
	}
	return (new_str);
}
