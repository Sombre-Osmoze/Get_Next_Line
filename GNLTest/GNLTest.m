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
	fileName = malloc(sizeof(char * ) * 2);
	fileName[1] = "/Users/marcusflorentin/Work-Pro-dev/Get_Next_Line/lol.txt";
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testGNL {

	NSString *allFile = [[NSString alloc] initWithContentsOfFile:@"/Users/marcusflorentin/Work-Pro-dev/Get_Next_Line/lol.txt" encoding: NSUTF8StringEncoding error:nil];

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

- (void)testClosenFileDescriptor {

	char *line = "Marcus";
	int test_fd = 42;


	close(test_fd);


	XCTAssertEqual(get_next_line(test_fd, &line), read(test_fd, &line, BUFF_SIZE), "Get_Next_Line ne retourne pas \"-1\" si le file descriptor est fermé");
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
