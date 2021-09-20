#include "segment_location.h"

bool various_side(Segment &seg1, Segment &seg2, Dot &point) {
    bool seg1_above_point = false, seg2_above_point = false;
    if (max(seg1.dot2.get_y(), seg1.dot1.get_y()) > point.get_y())
        seg1_above_point = true;
    if (max(seg2.dot2.get_y(), seg2.dot1.get_y()) > point.get_y())
        seg2_above_point = true;
    if (seg1_above_point != seg2_above_point)
        return true;
    else
        return false;
}