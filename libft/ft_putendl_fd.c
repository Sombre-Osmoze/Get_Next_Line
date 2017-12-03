/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:30:42 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/22 18:30:44 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(const char *s, int fd)
{
	char	c;

	c = '\n';
	if (s != NULL)
	{
		while (*s)
		{
			write(fd, s++, 1);
		}
		write(fd, &c, 1);
	}
}
