//
//  Point.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_POINT_H_
#define _FSN_POINT_H_

namespace fsn {
	struct Point {
		int x;
		int y;
	};
	
	bool operator==(const Point& a, const Point& b);
	bool operator!=(const Point& a, const Point& b);
	
	/*!
	 Compares two points. A point is less than another if its y coordinate is
	 smaller. If both points have the same y coordinate, the one with the
	 smaller x coordinate is chosen as the smaller point.
	 */
	bool operator<(const Point& a, const Point& b);
	bool operator<=(const Point& a, const Point& b);
	bool operator>(const Point& a, const Point& b);
	bool operator>=(const Point& a, const Point& b);
}


#endif /* _FSN_POINT_H_ */
