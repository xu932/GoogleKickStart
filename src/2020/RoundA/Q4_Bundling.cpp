#include <iostream>
#include <string>

using namespace std;


class Trie {
public:
    Trie* child[26] = {0x0};
    int children;
    Trie() : children(0) {}

    ~Trie() {
        for (auto p : child) {
            if (p != nullptr)   delete p;
        }
    }
};

void insert(Trie* cur, string s) {
    for (auto ch : s) {
        if (cur->child[ch - 'A'] == nullptr)    cur->child[ch - 'A'] = new Trie();
        cur = cur->child[ch - 'A'];
        cur->children++;
    }
}

int bundling_getScore(Trie* t, int K) {
    int ret = 0;
    for (auto p : t->child) {
        if (p == nullptr || p->children < K)    continue;
        ret += bundling_getScore(p, K);
    }
    ret += t->children / K;
    return ret;
}

int Bundling() {
    // Load all strings into Trie, and the level of any trie node is the length of prefix for the
    // current string. The number of strings with such prefix is cached in Trie.children. Then
    // recursively calculate the score. The score at given trie node is level * number of strings 
    // *remain* that can be put into groups of K, the idea of remain is any string being matched
    // by its children will not be counted.
    // Time: O(N * S) where S is the length of the longest string
    // Space: O(N * S)

    int N, K;
    cin >> N >> K;
    Trie* t = new Trie();
    string s;
    for (int i = 0; i < N; i++) {
        cin >> s;
        insert(t, s);
    }
    int score = bundling_getScore(t, K);
    
    delete t;
    return score;
}

int main(int argc, const char **argv) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << Bundling() << endl;
    }
    return 0;
}