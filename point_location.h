#ifndef TEST_PROBLEM_POINT_LOCATION_H
#define TEST_PROBLEM_POINT_LOCATION_H

#include "build_scanline.h"
#include "Segment.h"

bool point_outside_the_segment(const Dot &point, const Segment &segment);

bool point_between_segment(const Dot &point, const Segment &segment);

bool point_on_parallel_segment_y(const Dot &point, const Segment &segment);

bool point_on_dot_segment_y(const Dot &point, const Segment &segment);

bool point_into_line(const Dot &point, const Segment &cur_shell);

bool check_into(const vector<Segment> &shell, const Dot &point);

bool check_point_to_cur_contour(const Dot &point, const Segment &segment);

#endif
