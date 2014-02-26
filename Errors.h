//
//  Errors.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_ERRORS_H_
#define _FSN_ERRORS_H_

#include <stdio.h>
#include <stdlib.h>

#define fatal(fmt, args...) do { \
	fprintf(stderr, "Internal error: "); \
	fprintf(stderr, fmt, ##args); \
	exit(EXIT_FAILURE); \
} while(0)


#endif /* _FSN_ERRORS_H_ */
