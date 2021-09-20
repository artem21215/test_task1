#include "point_location.h"
#include "intersection_dot_with_segment.h"

bool check_into(const vector<Segment> &shell, const Dot &point) {
    vector<double> array_of_intersection = build_array_intersection(shell, point);
    sort(array_of_intersection.begin(), array_of_intersection.end());
    bool into = false;
    for (auto &cur_intersection:array_of_intersection) {
        if ((double) point.get_x() < cur_intersection)
            return into;
        into = !into;
    }
    return false;
}

bool point_outside_the_segment(const Dot &point, const Segment &segment) {
    return point.get_y() > max(segment.dot1.get_y(), segment.dot2.get_y()) ||
           point.get_y() < min(segment.dot1.get_y(), segment.dot2.get_y());
}

bool point_between_segment(const Dot &point, const Segment &segment) {
    return max(segment.dot1.get_y(), segment.dot2.get_y()) > point.get_y() &&
           min(segment.dot1.get_y(), segment.dot2.get_y()) < point.get_y();
}

bool point_on_parallel_segment_y(const Dot &point, const Segment &segment) {
    return segment.dot1.get_y() == segment.dot2.get_y() && segment.dot1.get_y() == point.get_y();
}

bool point_on_dot_segment_y(const Dot &point, const Segment &segment) {
    return (segment.dot1.get_y() == point.get_y() || segment.dot2.get_y() == point.get_y());
}

bool point_into_line(const Dot &point, const Segment &cur_shell) {
    double left = min(cur_shell.dot1.get_x(), cur_shell.dot2.get_x());
    double right = max(cur_shell.dot1.get_x(), cur_shell.dot2.get_x());
    double len = right - left;
    if (abs(point.get_x() - left) + abs(point.get_x() - right) - (len) < 0.0000000001)
        return true;
    else
        return false;

}

bool check_point_to_cur_contour(const Dot &point, const Segment &segment) {
    return (abs((double) point.get_x() - intersection(point, segment)) < 0.000000001) ||
           (point_on_parallel_segment_y(point, segment) && point_into_line(point, segment));
}