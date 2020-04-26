#include <vector>
#include <iostream>

using namespace std;

int64_t BusRoutes() {
    // Greedy problem: to finish everything as late as possible, then it much finish the 
    // last bus as late as possible, which is on day D - D % bus[N - 1]. Now it become a
    // sub-problem with N' = N - 1 and D' = D - D % bus[N - 1]. Repease until first bus,
    // the D' at this point is the optimal solution
    // Time: O(N)
    // Space: O(1) if not counting the input
    int N;
    int64_t D;
    cin >> N >> D;
    vector<int64_t> bus(N);
    for (int i = 0; i < N; i++) cin >> bus[i];
    for (int i = N - 1; i >= 0; i--) {
        D = D - D % bus[i];
    }
    return D;
}

int main(int argc, const char** argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << BusRoutes() << endl;
    }
}
