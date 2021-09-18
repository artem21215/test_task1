//
// Created by artem on 18.09.2021.
//

#include "Segment.h"

Segment::Segment(Dot dot1, Dot dot2) : dot1(dot1), dot2(dot2) {}

Segment::Segment(int x1, int y1, int x2, int y2) : dot1(Dot(x1, y1)), dot2(Dot(x2, y2)) {}