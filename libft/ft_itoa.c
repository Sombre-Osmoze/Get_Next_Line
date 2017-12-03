/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:18:51 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/22 16:18:52 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static int	ft_convert(int n)
{
	n = -n;
	return (n);
}

static char	*ft_allocate(int n, char *p, int i, int sign)
{
	p[i] = '\0';
	while (i--)
	{
		p[i] = n % 10 + 48;
		n /= 10;
	}
	if (sign == -1)
		p[0] = '-';
	return (p);
}

char		*ft_itoa(int n)
{
	int		i;
	int		tmp;
	char	*p;
	int		sign;

	sign = 1;
	i = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = ft_convert(n);
		i++;
		sign = -1;
	}
	tmp = n;
	while (tmp >= 10)
	{
		tmp /= 10;
		i++;
	}
	if ((p = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	return (ft_allocate(n, p, i, sign));
}
