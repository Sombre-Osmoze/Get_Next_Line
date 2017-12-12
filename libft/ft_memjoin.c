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
	
	body = NULL;
	body = malloc(sizeof(unsigned char) * (head_size + tail_size));
	if (body)
	{
		ft_memmove(body, head, head_size);
		ft_memmove(body + head_size - 1, tail, tail_size);
	}
	return (body);
}
