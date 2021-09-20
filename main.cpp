#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "Segment.h"
#include "initial_shell.h"

#define INF 1e9

using namespace std;

bool cmp(Segment a, Segment b) {
    if (min(a.dot1.get_x(), a.dot2.get_x()) == min(b.dot1.get_x(), b.dot2.get_x()))
        return max(a.dot1.get_x(), a.dot2.get_x()) < max(b.dot1.get_x(), b.dot2.get_x());
    return min(a.dot1.get_x(), a.dot2.get_x()) < min(b.dot1.get_x(), b.dot2.get_x());
}

void shell_show(int n, vector<Segment> &shell) {
    for (int i = 0; i < n; ++i) {
        cout << shell[i].dot1.get_x() << ' ' << shell[i].dot1.get_y() << ';' << shell[i].dot2.get_x() << ' '
             << shell[i].dot2.get_y() << endl;
    }
}

double intersection(Dot &point, Segment &segment) {
    if (point.get_y() > max(segment.dot1.get_y(), segment.dot2.get_y()) ||
        point.get_y() < min(segment.dot1.get_y(), segment.dot2.get_y()))
        return -INF;

    double left_point_of_segment_x = min(segment.dot1.get_x(), segment.dot2.get_x());
    double left_point_of_segment_y;
    if ((double) segment.dot1.get_x() == left_point_of_segment_x)
        left_point_of_segment_y = (double) segment.dot1.get_y();
    else
        left_point_of_segment_y = (double) segment.dot2.get_y();
    double hight = abs((double) segment.dot1.get_y() - (double) segment.dot2.get_y());
    double len = abs((double) segment.dot1.get_x() - (double) segment.dot2.get_x());
    if (hight == 0)
        return left_point_of_segment_x;
    double intersection = left_point_of_segment_x + abs((double) point.get_y() - left_point_of_segment_y) * len / hight;
    return intersection;
}

bool point_between_segment(Dot &point, Segment &segment) {
    return max(segment.dot1.get_y(), segment.dot2.get_y()) > point.get_y() &&
           min(segment.dot1.get_y(), segment.dot2.get_y()) < point.get_y();
}

bool point_on_parallel_segment_y(Dot &point, Segment &segment) {
    return segment.dot1.get_y() == segment.dot2.get_y() && segment.dot1.get_y() == point.get_y();
}

bool point_on_dot_segment_y(Dot &point, Segment &segment) {
    return (segment.dot1.get_y() == point.get_y() || segment.dot2.get_y() == point.get_y());
}

struct cmp_for_dot_map {
    bool operator()(Dot a, Dot b) const {
        if (a.get_x() == b.get_x())
            return a.get_y() < b.get_y();
        return a.get_x() < b.get_x();
    }
};

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

bool point_into_line(Dot &point, Segment &cur_shell) {
    double left = min(cur_shell.dot1.get_x(), cur_shell.dot2.get_x());
    double right = max(cur_shell.dot1.get_x(), cur_shell.dot2.get_x());
    double len = right - left;
    if (abs(point.get_x() - left) + abs(point.get_x() - right) - (right - left) < 0.0000000001)
        return true;
    else
        return false;

}

vector<pair<double, bool>> build_array_intersection(vector<Segment> &shell, Dot &point) {
    vector<pair<double, bool>> array_of_intersection;
    bool flag = false;
    double cur_intersection_x = -INF;
    int n = shell.size();
    for (int i = 0; i < n; ++i) {
        cur_intersection_x = intersection(point, shell[i]);
        if (abs((double) point.get_x() - cur_intersection_x) < 0.000000001) {
            array_of_intersection.clear();
            array_of_intersection.emplace_back(-INF, true);
            array_of_intersection.emplace_back(INF, true);
            return array_of_intersection;
        }
        if (point_between_segment(point, shell[i])) {
            cur_intersection_x = intersection(point, shell[i]);
            array_of_intersection.emplace_back(cur_intersection_x, true);
        } else if (point_on_parallel_segment_y(point, shell[i])) {
            if (point_into_line(point, shell[i])) {
                array_of_intersection.clear();
                array_of_intersection.emplace_back(-INF, true);
                array_of_intersection.emplace_back(INF, true);
                return array_of_intersection;
            }
            int pred = i - 1, next = i + 1;
            if (pred < 0)
                pred = n - 1;
            if (next > n - 1)
                next = 0;
            if (various_side(shell[pred], shell[next], point))
                array_of_intersection.emplace_back(cur_intersection_x, true);
        } else if (point_on_dot_segment_y(point, shell[i])) {
            int pred = i - 1, next = i + 1, ind;
            if (pred < 0)
                pred = n - 1;
            if (next > n - 1)
                next = 0;
            if (shell[pred].dot2.get_y() == point.get_y())
                ind = pred;
            else
                ind = next;
            if (ind == pred)
                continue;
            if (shell[ind].dot1.get_y() == shell[ind].dot2.get_y())
                continue;
            if (various_side(shell[ind], shell[i], point)) {
                array_of_intersection.emplace_back(cur_intersection_x, true);
            }
        }
    }
    return array_of_intersection;
}

bool check_into(vector<Segment> &shell, Dot &point) {
    vector<pair<double, bool>> array_of_intersection = build_array_intersection(shell, point);
    sort(array_of_intersection.begin(), array_of_intersection.end());
    bool into = false;
    for (auto &cur_intersection:array_of_intersection) {
        if ((double) point.get_x() < cur_intersection.first)
            return into;
        into = !into;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Segment> shell(n);
    vector<Dot> points(m);
    initial_shell(n, m, shell, points);
    //shell_show(n, shell);
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (check_into(shell, points[i])) {
            ++cnt;
            cout << points[i].get_x() << ' ' << points[i].get_y() << ' ' << '+' << endl;
        } else {
            cout << points[i].get_x() << ' ' << points[i].get_y() << ' ' << '-' << endl;
        }
    }
    cout << cnt << endl;
    return 0;
}