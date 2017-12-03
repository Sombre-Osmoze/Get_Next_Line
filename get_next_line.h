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

#define BUFF_SIZE 45

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

int			get_next_line(const int fd, char **line);
static int	ft_read_line(const int fd, char **line, char *data[]);
static void	ft_stock_data(const int fd, char *rest, char *data[]);

#endif
