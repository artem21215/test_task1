#ifndef TEST_PROBLEM_BUILD_SCANLINE_H
#define TEST_PROBLEM_BUILD_SCANLINE_H

#include "vector"
#include "Segment.h"

vector<double> build_array_intersection(vector<Segment> &shell, Dot &point);

bool reprocessing(Segment &segment, Dot &point);

#endif
