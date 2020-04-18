#include <iostream>
#include <vector>

using namespace std;

int plates_dp(vector<vector<int>>& memo, vector<vector<int>>& plates, int i, int p) {
    // We are looking at stacks [i:] to grab p plates, we know that the maximum we can get is
    // max(grab k plates from stack i and recur with (i + 1, p - k) for k in range [0, max(K, p)])
    if (p == 0)             return 0;
    if (i >= plates.size()) return 0;
    if (memo[i][p] != -1)   return memo[i][p];
    if ((plates.size() - i) * plates[0].size() < p) {
        // in case total remaining plates are less than p
        memo[i][p] = 0;
        return 0;
    }
    memo[i][p] = plates_dp(memo, plates, i + 1, p);
    for (int j = 0; j < plates[i].size() && j < p; j++) {
        memo[i][p] = max(memo[i][p], plates[i][j] + plates_dp(memo, plates, i + 1, p - 1 - j));
    }

    return memo[i][p];
}

int Plates() {
    // Use dynamic programming to solve this problem. See plates_dp for the logic. The input is
    // processed in a way that plates[i][j] is the total beauty value for top j plates in stack i
    // Time: O(N*K*P) takes O(K) to fill each entry in memoization table and the table has size
    // N*(P+1)
    // Space: O(N*P)
    int N, K, P;
    cin >> N >> K >> P;
    vector<vector<int>> plates(N, vector<int>(K));
    for (int i = 0; i < N; i++) {
        cin >> plates[i][0];
        for (int j = 1; j < K; j++) {
            cin >> plates[i][j];
            plates[i][j] += plates[i][j - 1];
        }
    }
    vector<vector<int>> memo(N, vector<int>(P + 1, -1));
    return plates_dp(memo, plates, 0, P);
}

int main(int argc, const char **argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << Plates() << endl;
    }
    return 0;
}