//
//  GNLTest.m
//  GNLTest
//
//  Created by Marcus Florentin on 26/05/2018.
//  Copyright © 2018 Marcus Florentin. All rights reserved.
//

#import "GNLTest.h"

@implementation GNLTest

- (void)setUp {
    [super setUp];

    // Put setup code here. This method is called before the invocation of each test method in the class.

	nbFD = 2;
	fileName = malloc(sizeof(char * ) * 3);
	fileName[1] = "/Users/marcusflorentin/Work-Pro-dev/Get_Next_Line/lol.txt";
	fileName[2] = "/Users/marcusflorentin/Work-Pro-dev/Get_Next_Line/File.txt";
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)test_error_handling {

	char 	*line = NULL;

	XCTAssertEqual(get_next_line(-99, NULL), -1);
	XCTAssertEqual(get_next_line(-1, NULL), -1);
	XCTAssertEqual(get_next_line(-10000, NULL), -1);
	XCTAssertEqual(get_next_line(1, NULL), -1);
	XCTAssertEqual(get_next_line(99, NULL), -1);

	XCTAssertEqual(get_next_line(-99, &line), -1);
	XCTAssertEqual(get_next_line(-1, &line), -1);
	XCTAssertEqual(get_next_line(-10000, &line), -1);

	/* Not opened fd */
	XCTAssertEqual(get_next_line(42, &line), -1);
}


- (void)testGNL {

	NSString *allFile = [[NSString alloc] initWithContentsOfFile:[NSString stringWithCString:fileName[1] encoding:NSUTF8StringEncoding] encoding: NSUTF8StringEncoding error:nil];

	NSMutableString *testFile = [@"" mutableCopy];

	char *line = NULL;
	int fd[nbFD];
	int i = 0;

	if (nbFD == 0 || nbFD == 1)
		return;

	while (i  < nbFD)
		fd[i++] = 0;
	i = 1;
	if (nbFD > 1)
	{
		while (i < nbFD) {
			fd[i - 1] = open(fileName[i], O_RDONLY);
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

				[testFile appendString:[NSString stringWithCString:line encoding:NSUTF8StringEncoding]];
				[testFile appendString:@"\n"];
				free(line);
			}

		}

		XCTAssertEqualObjects(testFile, allFile);
		i++;
	} while (i + 1 < nbFD);

	if (nbFD > 1)
		while (--i >= 0) {
			if (fd[i] != -1)
				close(fd[i]);
		}

	free(fileName);
}


/**
 Cette série de tests, s'occupe de vérifé les retours d'erreur de la fonction GNL pour un "File descriptor" ("FD") négatif
 */
- (void)testFiledescriptorsNegative {

	XCTAssertEqual(get_next_line(-99, nil), -1, "Mauvais retour : devrait retourné \"-1\"");
	XCTAssertEqual(get_next_line(-1, nil), -1, "Mauvais retour : devrait retourné \"-1\"");

}

- (void)testFew_lines_of_4 {

	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	write(fd, "efgh\n", 5);
	write(fd, "ijkl\n", 5);
	write(fd, "mnop\n", 5);
	write(fd, "qrst\n", 5);
	write(fd, "uvwx\n", 5);
	write(fd, "yzab\n", 5);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"abcd");
	free(line);

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"efgh");
	free(line);

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"ijkl");
	free(line);

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"mnop");
	free(line);

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"qrst");
	free(line);

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"uvwx");
	free(line);

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"yzab");
	free(line);

	ret = get_next_line(p[0], &line);
	XCTAssertEqual(ret, 0);
	free(line);

}

- (void)testgnl7_1 {

	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	int			errors;

	fd = open("gnl7_1.txt", O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && strcmp(line, "12345678") != 0)
				errors++;
			count_lines++;
			if (count_lines > 50)
				break ;
		}
		close(fd);
		XCTAssertEqual(count_lines, 1);
		XCTAssertEqual(errors, 0);
	}

}

- (void)testClosenFileDescriptor {

	char *line = "Marcus";
	int test_fd = 42;


	close(test_fd);


	XCTAssertEqual(get_next_line(test_fd, &line), read(test_fd, &line, BUFF_SIZE));
}

- (void)testLine_of_4 {

	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"abcd");
	ret = get_next_line(p[0], &line);
	XCTAssertEqual(ret, 0);
}

- (void)testMultiFileDescriptor {

	char *line = NULL;
	int fdA = open(fileName[1], O_RDONLY);
	int fdB = open(fileName[0], O_RDONLY);

	NSString *textA = [[NSString alloc] initWithContentsOfFile:[NSString stringWithCString:fileName[1] encoding:NSUTF8StringEncoding] encoding: NSUTF8StringEncoding error:nil];
	NSString *textB = [[NSString alloc] initWithContentsOfFile:[NSString stringWithCString:fileName[2] encoding:NSUTF8StringEncoding] encoding: NSUTF8StringEncoding error:nil];
	NSArray *linesA = [textA componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
	NSArray *linesB = [textA componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];

	get_next_line(fdA, &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], linesA[0]);
	free(line);

	get_next_line(fdB, &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], linesB[0]);
	free(line);

	get_next_line(fdA, &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], linesA[1]);
	free(line);

	close(fdA);
	close(fdB);
}

- (void)testPerformanceManRsync {
    // This is an example of a performance test case.
	int fd = open(fileName[2], O_RDONLY);
	char *line = NULL;
	char **p_line = &line;

    [self measureBlock:^{
        // Put the code you want to measure the time of here.
		while (get_next_line(fd, p_line))
		{
			if (*p_line){

				free(*p_line);
			}

		}

    }];

	close(fd);
}

@end
