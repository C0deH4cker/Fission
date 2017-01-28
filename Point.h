//
//  Point.h
//  Fission
//
//  Created by C0deH4cker on 2/23/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_POINT_H
#define FSN_POINT_H

#include <ostream>

namespace fsn {
    struct Point {
        int x;
        int y;
        
        size_t hash() const;
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
    
    // Used for printing debug information
    std::ostream& operator<<(std::ostream& os, Point pt);
}

// Allow std::hash<Point>
namespace std {
    template<>
    struct hash<fsn::Point> {
        size_t operator()(fsn::Point pt) const {
            return pt.hash();
        }
    };
}


#endif /* FSN_POINT_H */
