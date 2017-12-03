/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:08:15 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/22 17:08:16 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_putendl(const char *s)
{
	char	c;

	c = '\n';
	if (s != NULL)
	{
		while (*s)
		{
			write(1, s++, 1);
		}
		write(1, &c, 1);
	}
}
