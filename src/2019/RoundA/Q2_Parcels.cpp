#include <queue>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

void BFS(vector<string>& board, vector<vector<int>>& dist, int R, int C) {
    queue<tuple<int, int, int>> q;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '1') {
                dist[i][j] = 0;
                q.push(make_tuple(i, j, 0));
            }
        }
    }
    int i, j, c;
    while (!q.empty()) {
        i = get<0>(q.front());
        j = get<1>(q.front());
        c = get<2>(q.front());
        q.pop();
        if (i > 0 && dist[i - 1][j] == -1) {
            dist[i - 1][j] = c + 1;
            q.push(make_tuple(i - 1, j, c + 1));
        }
        if (i < R - 1 && dist[i + 1][j] == -1) {
            dist[i + 1][j] = c + 1;
            q.push(make_tuple(i + 1, j, c + 1));
        }
        if (j > 0 && dist[i][j - 1] == -1) {
            dist[i][j - 1] = c + 1;
            q.push(make_tuple(i, j - 1, c + 1));
        }
        if (j < C - 1 && dist[i][j + 1] == -1) {
            dist[i][j + 1] = c + 1;
            q.push(make_tuple(i, j + 1, c + 1));
        }
    }
}

bool verify(vector<vector<int>>& dist, int R, int C, int k) {
    // Check if all nodes can be reached within k distance by adding a new office. The
    // Manhattan distance of two nodes can be computed by max(abs(x1+y1-x2-y2), abs(x1-x1-x2+y2))
    // therefore we can cache max(x1+y1) min(x1+y1) max(x1-y1) min(x1-y1) and use that as
    // the boundary for all nodes with distance more than k. Then check all nodes as possible
    // candidate for new office and see if the distance to boundary by using the cached
    // value is within k or not
    // Time: O(RC)
    // Space: O(1)
    int max_sum = -1000, min_sum = 1000, max_dif = -1000, min_dif = 1000;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (dist[i][j] > k) {
                max_sum = max(max_sum, i + j);
                min_sum = min(min_sum, i + j);
                max_dif = max(max_dif, i - j);
                min_dif = min(min_dif, i - j);
            }
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (max_sum - i - j <= k
                && max_dif - i + j <= k
                && i + j - min_sum <= k
                && i - j - min_dif <= k
            ) {
                return true;
            }
        }
    }
    return false;
}

int Parcels() {
    // First use multi-source BFS to compute the manhattan distance for each node to its
    // closest existing office. Then perform binary search to see if we can have all nodes
    // to be at most distance k away from any offices
    // Time: O(RC lg(R+C)) assume checking takes O(RC)
    // Space: O(RC) to store the distance for all nodes
    int R, C;
    cin >> R >> C;
    vector<string> board(R);
    vector<vector<int>> dist(R, vector<int>(C, -1));
    for (int i = 0; i < R; i++) cin >> board[i];
    BFS(board, dist, R, C);

    int low = 0, high = R + C, k;
    while (low < high) {
        k = (low + high) >> 1;
        if (verify(dist, R, C, k))  high = k;
        else                        low = k + 1;
    }
    return low;
}

int main(int argc, const char** argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << Parcels() << endl;
    }
}
