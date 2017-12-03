/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:15:10 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/22 17:15:13 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	next(long nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
	}
	if (nb >= 10)
	{
		next(nb / 10);
		next(nb % 10);
	}
	else
		ft_putchar(nb + 48);
}

void		ft_putnbr(int nb)
{
	long trans;

	trans = nb;
	next(trans);
}
