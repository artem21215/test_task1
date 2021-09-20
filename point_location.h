#ifndef TEST_PROBLEM_POINT_LOCATION_H
#define TEST_PROBLEM_POINT_LOCATION_H

#include "build_scanline.h"
#include "Segment.h"

bool point_outside_the_segment(Dot &point, Segment &segment);

bool point_between_segment(Dot &point, Segment &segment);

bool point_on_parallel_segment_y(Dot &point, Segment &segment);

bool point_on_dot_segment_y(Dot &point, Segment &segment);

bool point_into_line(Dot &point, Segment &cur_shell);

bool check_into(vector<Segment> &shell, Dot &point);

bool check_point_to_cur_contour(Dot &point, Segment &segment);

#endif
