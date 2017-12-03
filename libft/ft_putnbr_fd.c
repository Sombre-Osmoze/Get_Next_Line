/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:50:15 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/22 18:50:16 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	next(long nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar('-', fd);
		nb = nb * -1;
	}
	if (nb >= 10)
	{
		next(nb / 10, fd);
		next(nb % 10, fd);
	}
	else
		ft_putchar(nb + 48, fd);
}

void		ft_putnbr_fd(int nb, int fd)
{
	long trans;

	trans = nb;
	next(trans, fd);
}
