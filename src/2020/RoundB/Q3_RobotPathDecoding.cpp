#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int64_t MOD = 1000000000;

int64_t mod(int64_t num) {
    num = num % MOD;
    return num < 0 ? num + MOD : num;
}

void RobotPathDecoding(int t) {
    // It's kind of like implementing a calculator. Use a stack to track the multiplier and
    // the movement in pair. Everytime it sees (, it push the current multiplier and movement
    // to stack. Everytime it sees ), it multiple the current movement by the multiplier in
    // stack and add the movement in stack.
    // Note: g++ mod is not the "mathematically" correct. The remainder should be in the range
    // [0, MOD) and should not be negative number
    // Time: O(N) where N is the length of the string
    // Space: O(K) where K is number of parentheses
    string seq;
    cin >> seq;
    int64_t n = 0;
    stack<int64_t> mul;
    stack<pair<int64_t, int64_t>> move;
    int64_t w = 0, h = 0;
    for (auto c : seq) {
        switch (c) {
            case '(':
                mul.push(n);
                move.push(make_pair(w, h));
                n = 0;
                w = h = 0;
                break;
            case ')':
                w = mod(w * mul.top() + move.top().first);
                h = mod(h * mul.top() + move.top().second);
                mul.pop();
                move.pop();
                break;
            case 'W':
                w--;
                break;
            case 'E':
                w++;
                break;
            case 'N':
                h--;
                break;
            case 'S':
                h++;
                break;
            default:
                n = n * 10 + c - '0';
        }
    }
    w = mod(w) + 1;
    h = mod(h) + 1;
    cout << "Case #" << t << ": " << w << " " << h << endl;
}

int main(int argc, const char** argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        RobotPathDecoding(i + 1);
    }
}
