//
//  main.c
//  Get_Next_Line
//
//  Created by Marcus Florentin on 28/11/2017.
//  Copyright © 2017 Marcus Florentin. All rights reserved.
//

#include "main.h"

int main(int argc, char *argv[])
{
	char *line = "";
	int fd[5];
	int i = 0;

	while (i  < 5)
		fd[i++] = 0;
	i = 1;
	if (argc > 1)
	{
		while (i < argc) {
			fd[i - 1] = open(argv[i], O_RDONLY);
			i++;
		}
		i = 0;
	}
	else
		fd[0] = 1;

	while (get_next_line(fd[i], &line))
	{
		ft_putendl(line);
		if (line){
			bzero(line, sizeof(&line));
			free(line);
		}
	}
	if (line) {
		ft_putendl(line);
		free(line);
	}
	if (argc > 1)
		while (--i >= 0) {
			if (fd[i] != -1)
				close(fd[i]);
		}

	return 0;
}
