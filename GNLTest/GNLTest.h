//
//  GNLTest.h
//  Get_Next_Line
//
//  Created by Marcus Florentin on 26/05/2018.
//  Copyright © 2018 Marcus Florentin. All rights reserved.
//

#ifndef GNLTest_h
#define GNLTest_h

#import <XCTest/XCTest.h>

	// MARK: - Testable Header
#import "../get_next_line.h"
#import "../main.h"

@interface GNLTest : XCTestCase {

	int nbFD;
	char **fileName;
}



@end


#endif /* GNLTest_h */
