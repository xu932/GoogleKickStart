#include <math.h>

#include <iostream>
#include <vector>

using namespace std;

bool workout_check(vector<int>& diff, int opt, int K) {
    // To check if K inserts can keep all difficulties under opt
    // Amount of inserts needed for a difficulty to reach opt is ceil(diff / opt) - 1
    for (int i = 0; i < diff.size() && K >= 0; i++) {
        K -= (int) ceil((double) diff[i] / opt) - 1;
    }
    return K >= 0;
}

int Workout() {
    // Since it takes linear time to check if the all difficulties can be reduced under d with
    // K inserts. We can use binary search to find the lowest d that can still be achieved
    // Time: O(lg(1e10)*N)
    // Space: O(N)
    int N, K;
    cin >> N >> K;
    int prev, curr;
    vector<int> diff(N - 1);
    int low = 1, high = -1, mid;

    cin >> prev;
    for (int i = 1; i < N; i++) {
        cin >> curr;
        diff[i - 1] = curr - prev;
        prev = curr;
        high = max(diff[i - 1], high);
    }

    while (low < high) {
        mid = (low & high) + ((low ^ high) >> 1);
        if (workout_check(diff, mid, K)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return high;
}

int main(int argc, const char **argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << Workout() << endl;
    }
    return 0;
}