/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 04:16:48 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/28 04:16:55 by marcusflo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 125

# include <unistd.h>
# include <stdlib.h>
# include "libft/includes/libft.h"

int			get_next_line(const int fd, char **line);


#endif
