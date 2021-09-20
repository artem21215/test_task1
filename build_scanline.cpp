#include "point_location.h"
#include "segment_location.h"
#include "intersection_dot_with_segment.h"

bool reprocessing(const Segment &segment, const Dot &point) {
    return segment.dot2.get_y() == point.get_y();
}

vector<double> build_array_intersection(const vector<Segment> &shell, const Dot &point) {
    vector<double> array_of_intersection;
    int n = shell.size();
    for (int i = 0; i < n; ++i) {
        double cur_intersection_x = intersection(point, shell[i]);
        int pred = (i - 1 + n) % n, next = (i + 1) % n;
        if (point_between_segment(point, shell[i])) {
            array_of_intersection.push_back(cur_intersection_x);
        } else if (point_on_parallel_segment_y(point, shell[i])) {
            if (various_side(shell[pred], shell[next], point))
                array_of_intersection.push_back(cur_intersection_x);
        } else if (point_on_dot_segment_y(point, shell[i])) {
            if (various_side(shell[next], shell[i], point) && !reprocessing(shell[pred], point)) {
                array_of_intersection.push_back(cur_intersection_x);
            }
        }
        if (check_point_to_cur_contour(point, shell[i])) {
            array_of_intersection.clear();
            array_of_intersection.push_back(-INF);
            array_of_intersection.push_back(INF);
            return array_of_intersection;
        }
    }
    return array_of_intersection;
}