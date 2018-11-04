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
	fileName[2] = "/Users/marcusflorentin/Work-Pro-dev/Get_Next_Line/Tests/File.txt";

	
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)test_gnl1_1 {
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "TestFiles/gnl1_1.txt";
	fd = open(filename, O_RDONLY);
	if (fd != -1)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && strcmp(line, "1234567") != 0)
				errors++;
			count_lines++;
			if (count_lines > 50)
				break;
		}
		close(fd);
		XCTAssertEqual(count_lines, 1, "-> must have returned '1' once instead of %d time(s)\n", count_lines);
		XCTAssertEqual(errors, 0, "-> must have read \"1234567\" instead of \"%s\"\n", line);
	}
	else
		XCTFail("An error occured while opening file %s\n", filename);
}

- (void)test_line_of_16_without_nl {
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "mnopqrstuvwxyzab", 16);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"mnopqrstuvwxyzab");

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
	close(42);
	XCTAssertEqual(get_next_line(42, &line), -1);
}

- (void)testreturn_values {
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		gnl_ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abc\n\n", 5);
	close(p[1]);
	dup2(out, fd);

	/* Read abc and new line */
	gnl_ret = get_next_line(p[0], &line);
	XCTAssertEqual(gnl_ret, 1);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"abc");

	/* Read new line */
	gnl_ret = get_next_line(p[0], &line);
	XCTAssertEqual(gnl_ret, 1);
	if (line != NULL && *line) {
		XCTFail();
	}

	/* Read again, but meet EOF */
	gnl_ret = get_next_line(p[0], &line);
	XCTAssertEqual(gnl_ret, 0);
	if (line != NULL && *line) {
		XCTFail();
	}

	/* Let's do it once again */
	gnl_ret = get_next_line(p[0], &line);
	XCTAssertEqual(gnl_ret, 0);
	if (line != NULL && *line) {
		XCTFail();
	}
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

	XCTAssertEqual(get_next_line(-99, NULL), -1, "Mauvais retour : devrait retourné \"-1\"");
	XCTAssertEqual(get_next_line(-1, NULL), -1, "Mauvais retour : devrait retourné \"-1\"");

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

- (void)test_gnl7_1 {

	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	int			errors;

	fd = open("TestFiles/gnl7_1.txt", O_RDONLY);
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

- (void)test_gnl7_2 {

	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "TestFiles/gnl7_2.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && strcmp(line, "1234567") != 0)
				errors++;
			if (count_lines == 1 && strcmp(line, "abcdefgh") != 0)
				errors++;
			count_lines++;
			if (count_lines > 50)
				break ;
		}
		close(fd);
		XCTAssertEqual(count_lines, 2, "-> must have returned '1' twice instead of %d time(s)\n", count_lines);
		XCTAssertEqual(0, errors,"-> must have read \"1234567\" and \"abcdefgh\"\n");
		if (errors > 0)
			printf("-> must have read \"1234567\" and \"abcdefgh\"\n");
		if (count_lines == 2 && errors == 0)
			printf("OK\n");
	}
	else
		printf("An error occured while opening file %s\n", filename);

}

- (void)test_test_large_file {
	char *line;
	int fd;
	int fd2;
	int fd3;
	int	diff_file_size;

	system("mkdir -p sandbox");
	system("openssl rand -out sandbox/large_file.txt -base64 $((50 * 1000 * 3/4)) 2> /dev/null");

	fd = open("sandbox/large_file.txt", O_RDONLY);
	fd2 = open("sandbox/large_file.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);

	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		write(fd2, "\n", 1);
	}

	close(fd);
	close(fd2);

	system("diff sandbox/large_file.txt sandbox/large_file.txt.mine > sandbox/large_file.diff");
	fd3 = open("sandbox/large_file.diff", O_RDONLY);
	diff_file_size = read(fd3, NULL, 10);
	close(fd3);

	XCTAssertEqual(diff_file_size, 0);
}

- (void)test_line_without_nl {
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd", 4);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"abcd");
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
	int fdB = open(fileName[2], O_RDONLY);

	NSString *textA = [[NSString alloc] initWithContentsOfFile:[NSString stringWithCString:fileName[1] encoding:NSUTF8StringEncoding] encoding: NSUTF8StringEncoding error:nil];
	NSString *textB = [[NSString alloc] initWithContentsOfFile:[NSString stringWithCString:fileName[2] encoding:NSUTF8StringEncoding] encoding: NSUTF8StringEncoding error:nil];
	NSArray *linesA = [textA componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
	NSArray *linesB = [textB componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];

	get_next_line(fdA, &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], linesA[0]);
	if (line)
		free(line);

	get_next_line(fdB, &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], linesB[0]);
	if (line)
		free(line);

	get_next_line(fdA, &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], linesA[1]);
	if (line)
		free(line);

	close(fdA);
	close(fdB);
}

-(void)test_bonus_multiple_fd {

	char	*line_fd0;
	int		p_fd0[2];
	int		fd0 = 0;
	int		out_fd0 = dup(fd0);

	char	*line_fd1;
	int		p_fd1[2];
	int		fd1 = 1;
	int		out_fd1 = dup(fd1);

	char	*line_fd2;
	int		p_fd2[2];
	int		fd2 = 2;
	int		out_fd2 = dup(fd2);

	char	*line_fd3;
	int		p_fd3[2];
	int		fd3 = 3;
	int		out_fd3 = dup(fd3);

	pipe(p_fd0);
	dup2(p_fd0[1], fd0);
	write(fd0, "aaa\nbbb\n", 8);
	dup2(out_fd0, fd0);
	close(p_fd0[1]);

	pipe(p_fd1);
	dup2(p_fd1[1], fd1);
	write(fd1, "111\n222\n", 8);
	dup2(out_fd1, fd1);
	close(p_fd1[1]);

	pipe(p_fd2);
	dup2(p_fd2[1], fd2);
	write(fd2, "www\nzzz\n", 8);
	dup2(out_fd2, fd2);
	close(p_fd2[1]);

	pipe(p_fd3);
	dup2(p_fd3[1], fd3);
	write(fd3, "888\n999\n", 8);
	dup2(out_fd3, fd3);
	close(p_fd3[1]);

	get_next_line(p_fd0[0], &line_fd0);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line_fd0], @"aaa");

	get_next_line(p_fd1[0], &line_fd1);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line_fd1], @"111");

	get_next_line(p_fd2[0], &line_fd2);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line_fd2], @"www");

	get_next_line(p_fd3[0], &line_fd3);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line_fd3], @"888");

	get_next_line(p_fd0[0], &line_fd0);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line_fd0], @"bbb");

	get_next_line(p_fd1[0], &line_fd1);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line_fd1], @"222");

	get_next_line(p_fd2[0], &line_fd2);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line_fd2], @"zzz");

	get_next_line(p_fd3[0], &line_fd3);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line_fd3], @"999");

}

- (void)test_few_lines_of_16 {
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcdefghijklmnop\n", 17);
	write(fd, "qrstuvwxyzabcdef\n", 17);
	write(fd, "ghijklmnopqrstuv\n", 17);
	write(fd, "wxyzabcdefghijkl\n", 17);
	write(fd, "mnopqrstuvwxyzab\n", 17);
	write(fd, "cdefghijklmnopqr\n", 17);
	write(fd, "stuvwxzabcdefghi\n", 17);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"abcdefghijklmnop");

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"qrstuvwxyzabcdef");

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"ghijklmnopqrstuv");

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"wxyzabcdefghijkl");

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"mnopqrstuvwxyzab");

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"cdefghijklmnopqr");;;

	get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:line], @"stuvwxzabcdefghi");

	ret = get_next_line(p[0], &line);
	XCTAssertEqual(ret, 0);
}


- (void)test_medium_string {
	char 	*line;
	int		out;
	int		p[2];
	char 	*str;
	int		gnl_ret;

	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tem pus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	write(1, str, strlen(str));
	close(p[1]);
	dup2(out, 1);
	gnl_ret = get_next_line(p[0], &line);
	XCTAssertEqualObjects([NSString stringWithUTF8String:str], [NSString stringWithUTF8String:line]);

	if (!(gnl_ret == 0 || gnl_ret == 1)) {
		XCTFail();
	}
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
