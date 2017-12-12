/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memichr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 06:16:19 by mflorent          #+#    #+#             */
/*   Updated: 2017/12/12 06:16:21 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_memichr(const void *src, char chr, size_t len)
{
	unsigned char	*p_src;
	size_t	i;
	
	i = 0;
	p_src = (unsigned char *)src;
	while (i < len)
	{
		if (p_src[i] == (unsigned char)chr)
			return (i);
		i++;
		p_src++;
	}
	return (-1);
}
