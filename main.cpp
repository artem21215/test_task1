#include "Segment.h"
#include "initial_shell.h"
#include "point_location.h"

int main() {
    int n, m;
    cin >> n >> m;
    vector<Segment> shell(n);
    vector<Dot> points(m);
    initial_shell(n, m, shell, points);
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (check_into(shell, points[i]))
            ++cnt;
    }
    cout << cnt << endl;
    return 0;
}