#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int Training() {
    int N, P;
    cin >> N >> P;
    vector<int> skill(N);
    for (int i = 0; i < N; i++) cin >> skill[i];
    sort(skill.begin(), skill.end());

    int sum = 0, i;
    for (i = 0; i < P; i++) sum += skill[i];
    int ret = skill[i - 1] * P - sum;

    for (; i < N; i++) {
        sum += skill[i] - skill[i - P];
        ret = min(ret, skill[i] * P - sum);
    }
    return ret;
}

int main(int argc, const char** argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << Training() << endl;
    }
}
