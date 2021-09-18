#include "Segment.h"
void initial_shell(int &n, int m, vector<Segment> &shell, vector<Dot> &points) {
    int cnt = 0, pred_x, pred_y;
    for (int i = 0; i < 2 * n; ++i) {
        int x, y;
        cin >> x >> y;
        if (i == 0) {
            pred_x = x;
            pred_y = y;
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
    n = cnt;
    shell.resize(n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        points[i] = Dot(x, y);
    }
}
