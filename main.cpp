#include <iostream>
#include <vector>
#include <algorithm>
#include "Segment.h"
#include "initial_shell.h"

using namespace std;

bool cmp(Segment a, Segment b) {
    if (min(a.dot1.get_x(), a.dot2.get_x()) == min(b.dot1.get_x(), b.dot2.get_x()))
        return max(a.dot1.get_x(), a.dot2.get_x()) < max(b.dot1.get_x(), b.dot2.get_x());
    else
        return min(a.dot1.get_x(), a.dot2.get_x()) < min(b.dot1.get_x(), b.dot2.get_x());
}

void shell_show(int n, vector<Segment> &shell) {
    for (int i = 0; i < n; ++i) {
        cout << shell[i].dot1.get_x() << ' ' << shell[i].dot1.get_y() << ';' << shell[i].dot2.get_x() << ' '
             << shell[i].dot2.get_y() << endl;
    }
}

int intersection(Dot &point, Segment &segment) {
    int left_point_of_segment = min(segment.dot1.get_x(), segment.dot2.get_x());
    int hight = abs(segment.dot1.get_y() - segment.dot2.get_y());
    int len = abs(segment.dot1.get_x() - segment.dot2.get_x());
    int ans = left_point_of_segment + abs(point.get_x() - left_point_of_segment) * len / hight;
    if (abs(point.get_x() - left_point_of_segment) * len % hight != 0)
        ++ans;
    return ans;
}

bool point_between_segment(Dot &point, Segment &segment) {
    return max(segment.dot1.get_y(), segment.dot2.get_y()) > point.get_y() &&
           min(segment.dot1.get_y(), segment.dot2.get_y()) < point.get_y();
}

bool check_into(int n, vector<Segment> &shell, int m, vector<Dot> &points) {
    bool into = false;
    int intersection_x;
    for (auto &point:points) {
        for (auto &segment:shell) {
            if (point_between_segment(point, segment)) {
                intersection_x = intersection(point, segment);
                if (!into) {
                    if (point.get_x() < intersection_x)
                        return false;
                } else {
                    if (point.get_x() <= intersection_x)
                        return true;
                }
                into = !into;
            }

        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Segment> shell(2 * n);
    vector<Dot> points(m);
    initial_shell(n, m, shell, points);
    sort(shell.begin(), shell.end(), cmp);
    shell_show(n, shell);
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (check_into(n, shell, m, points))
            ++cnt;
    }
    cout << cnt << endl;
    return 0;
}