//
// Created by artem on 20.09.2021.
//

#include "intersection_dot_with_segment.h"
#include "point_location.h"

double intersection(const Dot &point, const Segment &segment) {
    if (point_outside_the_segment(point, segment))
        return -INF;

    double left_point_of_segment_x = min(segment.dot1.get_x(), segment.dot2.get_x());
    double left_point_of_segment_y;
    if (abs((double) segment.dot1.get_x() - left_point_of_segment_x) < 0.000000001)
        left_point_of_segment_y = (double) segment.dot1.get_y();
    else
        left_point_of_segment_y = (double) segment.dot2.get_y();
    double height = abs((double) segment.dot1.get_y() - (double) segment.dot2.get_y());
    double len = abs((double) segment.dot1.get_x() - (double) segment.dot2.get_x());
    if (height == 0)
        return left_point_of_segment_x;
    double intersection =
            left_point_of_segment_x + abs((double) point.get_y() - left_point_of_segment_y) * len / height;
    return intersection;
}