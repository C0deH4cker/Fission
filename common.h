//
//  macros.h
//  Fission
//
//  Created by C0deH4cker on 2/28/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_MACROS_H
#define FSN_MACROS_H

#include <cstdio>
#include <cstdlib>

#define fatal(fmt, args...) do { \
	fprintf(stderr, "Internal error: "); \
	fprintf(stderr, fmt, ##args); \
	exit(EXIT_FAILURE); \
} while(0)

#define ENUM_BINOP(name, type, op) \
static inline name operator op(name a, name b) { \
	return name(type(a) op type(b)); \
}

#define ENUM_BINEQ(name, type, op) \
static inline name& operator op##=(name& a, name b) { \
	return a = name(type(a) op type(b)); \
}

#define ENUM_OP(name, type, op) \
ENUM_BINOP(name, type, op) \
ENUM_BINEQ(name, type, op)

#define ENUM_BITFIELD(name, type) \
enum class name: type; \
ENUM_OP(name, type, &) \
ENUM_OP(name, type, |) \
ENUM_OP(name, type, ^) \
static inline name operator~(name val) { \
	return name(~type(val)); \
} \
enum class name: type

#endif /* FSN_MACROS_H */
