//
//  macros.h
//  Fission
//
//  Created by C0deH4cker on 2/28/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_MACROS_H_
#define _FSN_MACROS_H_

#include <stdio.h>
#include <stdlib.h>

#define fatal(fmt, args...) do { \
	fprintf(stderr, "Internal error: "); \
	fprintf(stderr, fmt, ##args); \
	exit(EXIT_FAILURE); \
} while(0)

#define ABS(x) ({ \
	__typeof__(x) _x = (x); \
	_x < 0 ? -_x : _x; \
})

#define CMP(op, a, b) ({ \
	__typeof__(a) _a = (a); \
	__typeof__(b) _b = (b); \
	(_a op _b) ? _a : _b; \
})

#define MAX(a, b) CMP(>, a, b)
#define MIN(a, b) CMP(<, a, b)


#endif /* _FSN_MACROS_H_ */
