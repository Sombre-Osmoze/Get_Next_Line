/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorent <mflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 18:26:47 by mflorent          #+#    #+#             */
/*   Updated: 2017/12/11 18:26:50 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memjoin(void *head, size_t head_size, void *tail, size_t tail_size)
{
	unsigned char	*body;

	body = ft_memalloc(sizeof(unsigned char) * (head_size + tail_size));
	if (body)
	{
		if (head)
			ft_memmove(body, head, head_size);
		if (tail)
			ft_memmove(body + head_size, tail, tail_size);
	}
	return (body);
}
