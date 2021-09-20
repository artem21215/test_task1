#ifndef TEST_PROBLEM_BUILD_SCANLINE_H
#define TEST_PROBLEM_BUILD_SCANLINE_H

#include "vector"
#include "Segment.h"

vector<double> build_array_intersection(const vector<Segment> &shell, const Dot &point);

bool reprocessing(const Segment &segment, const Dot &point);

#endif
