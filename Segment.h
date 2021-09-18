#ifndef TEST_PROBLEM_SEGMENT_H
#define TEST_PROBLEM_SEGMENT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Dot.h"

using namespace std;

class Segment : public Dot {
public:
    Dot dot1{}, dot2{};

    Segment() = default;

    Segment(Dot dot1, Dot dot2);

    Segment(int x1, int y1, int x2, int y2);
};

#endif
