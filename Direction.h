//
//  Direction.h
//  Fission
//
//  Created by C0deH4cker on 2/25/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_DIRECTION_H
#define FSN_DIRECTION_H

/*! Represents a simple direction, either up, down, left, or right */
typedef unsigned char Direction;

/* Chosen carefully for easy bitwise operations */
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3
#define UNKNOWN 0xff


#endif /* FSN_DIRECTION_H */
