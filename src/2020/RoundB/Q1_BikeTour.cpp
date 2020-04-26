#include <iostream>

using namespace std;

int BikeTour() {
    int N;
    cin >> N;
    int prev, curr, next, ret = 0;
    cin >> prev >> curr;
    for (int i = 2; i < N; i++) {
        cin >> next;
        ret += curr > prev && curr > next ? 1 : 0;
        prev = curr;
        curr = next;
    }
    return ret;
}

int main(int argc, const char** argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << BikeTour() << endl;
    }
}
