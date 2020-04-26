#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


int Allocation() {
    // Sort the prices and start buying from the one with lowest price.
    // Time: O(n*lg(n))
    // Space: O(n) for the prices
    int N, B;
    cin >> N >> B;
    vector<int> prices(N, 0);
    for (int i = 0; i < N; i++)     cin >> prices[i];
    sort(prices.begin(), prices.end());
    int result = 0;
    for (int i = 0; i < N && B >= prices[i]; i++) {
        result++;
        B -= prices[i];
    }
    return result;
}

int main(int argc, const char **argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << Allocation() << endl;
    }
    return 0;
}