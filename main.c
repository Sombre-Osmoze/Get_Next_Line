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

	char **line = NULL;
	int fd = 0;
	int i = 1;

	if (argc > 1)
	{
		while (i < argc) {
			fd = open(argv[i++], O_RDONLY);
			while (get_next_line(fd, line))
				printf("%d : %s", fd, *line);
			close(fd);
		}
	}
	else
		get_next_line(1, line);

	return 0;
}

