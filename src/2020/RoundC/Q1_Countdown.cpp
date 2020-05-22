#include <iostream>
#include <vector>

using namespace std;

int Countdown() {
    // check stores the number expected to be seen for a valid countdown
    int K, N;
    cin >> N >> K;
    int check = K, ret = 0;
    vector<int> arr(N);
    for (int i = 0 ; i < N; i++) {
        if (check == 0) {
            check = K;
            ret++;
        }
        cin >> arr[i];
        if (arr[i] == check)    check--;
        else if (arr[i] == K)   check = K - 1;
        else                    check = K;
    }
    ret += check == 0;
    return ret;
}

int main(int argc, const char** srgv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << Countdown() << endl;
    }
}
