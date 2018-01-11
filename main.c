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
	char *line = NULL;
	int fd[argc];
	int i = 0;

	while (i  < argc)
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

	do {
//		if (argv[i + 1])
//			printf("Fichier : %s\n", argv[i + 1]);

		while (get_next_line(fd[i], &line))
		{
			if (line){
					//			sleep(2);
				ft_putendl(line);
				free(line);
			}

		}
		i++;
	} while (i + 1 < argc);

	if (argc > 1)
		while (--i >= 0) {
			if (fd[i] != -1)
				close(fd[i]);
		}

	return 0;
}
