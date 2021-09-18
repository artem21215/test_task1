#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "Segment.h"
#include "initial_shell.h"

using namespace std;

bool cmp(Segment a, Segment b) {
    return min(a.dot1.get_x(), a.dot2.get_x()) < min(b.dot1.get_x(), b.dot2.get_x());
}

void shell_show(int n, vector<Segment> &shell) {
    for (int i = 0; i < n; ++i) {
        cout << shell[i].dot1.get_x() << ' ' << shell[i].dot1.get_y() << ';' << shell[i].dot2.get_x() << ' '
             << shell[i].dot2.get_y() << endl;
    }
}

int intersection(Dot &point, Segment &segment) {
    int left_point_of_segment_x = min(segment.dot1.get_x(), segment.dot2.get_x());
    int left_point_of_segment_y;
    if (segment.dot1.get_x() == left_point_of_segment_x)
        left_point_of_segment_y = segment.dot1.get_y();
    else
        left_point_of_segment_y = segment.dot2.get_y();
    int hight = abs(segment.dot1.get_y() - segment.dot2.get_y());
    int len = abs(segment.dot1.get_x() - segment.dot2.get_x());
    int ans = left_point_of_segment_x + abs(point.get_y() - left_point_of_segment_y) * len / hight;
    if (abs(point.get_y() - left_point_of_segment_y) * len % hight != 0)
        ++ans;
    return ans;
}

bool point_between_segment(Dot &point, Segment &segment) {
    return max(segment.dot1.get_y(), segment.dot2.get_y()) > point.get_y() &&
           min(segment.dot1.get_y(), segment.dot2.get_y()) < point.get_y();
}

bool point_on_parallel_segment(Dot &point, Segment &segment) {
    return segment.dot1.get_y() == segment.dot2.get_y() && segment.dot1.get_y() == point.get_y();
}

struct cmp_for_dot_map {
    bool operator()(Dot a, Dot b) const {
        if (a.get_x() == b.get_x())
            return a.get_y() < b.get_y();
        return a.get_x() < b.get_x();
    }
};

bool check_into(vector<Segment> &shell, int i, vector<Dot> &points,
                map<Dot, Dot, cmp_for_dot_map> &navigate_segments_right,
                map<Dot, Dot, cmp_for_dot_map> &navigate_segments_left) {
    Dot point = Dot(points[i].get_x(), points[i].get_y());
    bool into = false;
    int intersection_x;
    for (auto &segment:shell) {
        if (point_between_segment(point, segment)) {
            intersection_x = intersection(point, segment);
            if (!into) {
                if (point.get_x() < intersection_x) {
                    return false;
                }
            } else {
                if (point.get_x() <= intersection_x) {
                    return true;
                }
            }
            into = !into;
        } else if (point_on_parallel_segment(point, segment)) {
            Segment seg1, seg2;
            seg1 = Segment(segment.dot1, navigate_segments_right[segment.dot1]);
            seg2 = Segment(segment.dot2, navigate_segments_left[segment.dot2]);
            if (seg1.dot1.get_y() == seg1.dot2.get_y()) {
                seg1 = Segment(segment.dot2, navigate_segments_right[segment.dot2]);
                seg2 = Segment(segment.dot1, navigate_segments_left[segment.dot1]);
            }
            bool seg1_above_point = false, seg2_above_point = false;
            if (seg1.dot2.get_y() > point.get_y())
                seg1_above_point = true;
            if (seg2.dot2.get_y() > point.get_y())
                seg2_above_point = true;
            if (!into) {
                if (point.get_x() < min(segment.dot1.get_x(), segment.dot2.get_x()))
                    return false;
            } else {
                if (point.get_x() <= min(segment.dot1.get_x(), segment.dot2.get_x()))
                    return true;
            }
            if (point.get_x() <= max(segment.dot1.get_x(), segment.dot2.get_x()))
                return true;
            if (seg1_above_point != seg2_above_point)
                into = !into;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Segment> shell(n);
    vector<Dot> points(m);
    initial_shell(n, m, shell, points);
    map<Dot, Dot, cmp_for_dot_map> navigate_segments_right, navigate_segments_left;
    for (auto &segment:shell) {
        navigate_segments_right[segment.dot1] = segment.dot2;
        navigate_segments_left[segment.dot2] = segment.dot1;
    }
    sort(shell.begin(), shell.end(), cmp);
    //shell_show(n, shell);
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (check_into(shell, i, points, navigate_segments_left, navigate_segments_right)) {
            ++cnt;
            cout << points[i].get_x() << ' ' << points[i].get_y() << ' ' << '+' << endl;
        } else {
            cout << points[i].get_x() << ' ' << points[i].get_y() << ' ' << '-' << endl;
        }
    }
    cout << cnt << endl;
    return 0;
}