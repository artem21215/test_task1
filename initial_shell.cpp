#include "Segment.h"

void initial_shell(int &n, int m, vector<Segment> &shell, vector<Dot> &points) {
    int cnt = 0, pred_x, pred_y;
    bool parallel = false;
    Dot parallel_end;
    for (int i = 0; i < 2 * n; ++i) {
        int x, y;
        cin >> x >> y;
        if (i == 0) {
            pred_x = x;
            pred_y = y;
            continue;
        }
        if (x == pred_x && y == pred_y)
            continue;
        if (pred_y == y && !parallel) {
            parallel = true;
        }
        if (parallel && y != pred_y) {
            parallel = false;
            shell[cnt].dot1 = Dot(pred_x, pred_y);
            shell[cnt].dot2 = Dot(parallel_end);
            pred_x = parallel_end.get_x();
            pred_y = parallel_end.get_y();
            ++cnt;
        }
        if (parallel) {
            parallel_end = Dot(x, y);
            continue;
        }
        if (x != pred_x || y != pred_y) {
            shell[cnt].dot1 = Dot(pred_x, pred_y);
            shell[cnt].dot2 = Dot(x, y);
            pred_x = x;
            pred_y = y;
            ++cnt;
        }
    }
    if (parallel) {
        if (shell[0].dot2.get_y() == parallel_end.get_y()) {
            shell[0].dot1 = Dot(pred_x, pred_y);
        } else {
            ++cnt;
            shell[cnt].dot1 = Dot(pred_x, pred_y);
            shell[cnt].dot2 = Dot(parallel_end.get_x(), parallel_end.get_y());
        }
    }
    n = cnt;
    shell.resize(n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        points[i] = Dot(x, y);
    }
}
