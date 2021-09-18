#include "Segment.h"

void initial_shell(int &n, int m, vector<Segment> &shell, vector<Dot> &points) {
    int x, y;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        shell[i].dot1 = Dot(x, y);
        cin >> x >> y;
        shell[i].dot2 = Dot(x, y);
    }
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        points[i] = Dot(x, y);
    }
}
