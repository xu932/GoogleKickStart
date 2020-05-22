#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool dfs(vector<unordered_set<int>>& g, unordered_map<int, int>& visited, string& ret, int i) {
    visited[i] = 1;
    for (auto next : g[i]) {
        if (visited[next] == 1) return false;
        if (visited[next] == 0 && !dfs(g, visited, ret, next)) {
            return false;
        }
    }
    ret += string(1, char(i + 'A'));
    visited[i] = 2;
    return true;
}

string StableWall() {
    // Given a polyominos A, all blocks that is below each square of A that are neither A nor 
    // ground need to be placed before A - this can be seen as an edge from A to other polyominos
    // For example:
    // ZOAAMM
    // ZOAOMM
    // ZOOOOM
    // ZZZZOM
    // some blocks of A is above O, so there is an edge from A to O: A -> O
    // some blocks of O is above Z, so there is an edge from O to Z: O -> Z
    // After these edges are identified, the problem become finding a topological order if
    // exist. This can be done through DFS.
    // Time complexity: O(V+E)=O(N^2)=O(26*26) for DFS and O(R*C) for building the graph
    //                  total would be O(N^2+RC)
    // Space complexity: O(N^2) to store the edges + visited state map
    int R, C;
    cin >> R >> C;
    vector<string> wall(R);
    for (int i = 0; i < R; i++) cin >> wall[i];
    vector<unordered_set<int>> g(26);
    unordered_map<int, int> visited;
    
    for (int j = 0; j < C; j++) visited[wall[R - 1][j] - 'A'] = 0;
    for (int i = R - 2; i >= 0; i--) {
        for (int j = 0; j < C; j++) {
            visited[wall[i][j] - 'A'] = 0;
            if (wall[i][j] != wall[i + 1][j]) {
                g[wall[i][j] - 'A'].insert(wall[i + 1][j] - 'A');
            }
        }
    }
    string ret = "";
    for (auto &p : visited) {
        if (p.second == 0) {
            if (!dfs(g, visited, ret, p.first)) return "-1";
        }
    }
    return ret;
}

int main(int argc, const char** srgv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << StableWall() << endl;
    }
}
