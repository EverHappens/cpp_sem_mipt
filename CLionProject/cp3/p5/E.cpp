#include <iostream>

struct Node {
    long long val = 0;
    Node *c[2]{};

    Node() {
        c[0] = c[1] = nullptr;
    }

    void upd(int ind, int v, int L = 0, int R = 1e9) { // add v
        if (L == ind && R == ind) {
            val += v;
            return;
        }
        int M = (L + R) / 2;
        if (ind <= M) {
            if (!c[0]) c[0] = new Node();
            c[0]->upd(ind, v, L, M);
        } else {
            if (!c[1]) c[1] = new Node();
            c[1]->upd(ind, v, M + 1, R);
        }
        val = 0;
        if (c[0]) val += c[0]->val;
        if (c[1]) val += c[1]->val;
    }

    long long query(int lo, int hi, int L = 0, int R = 1e9 - 1) { // query sum of segment
        if (hi < L || R < lo) return 0;
        if (lo <= L && R <= hi) return val;
        int M = (L + R) / 2;
        long long res = 0;
        if (c[0]) res += c[0]->query(lo, hi, L, M);
        if (c[1]) res += c[1]->query(lo, hi, M + 1, R);
        return res;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    Node node;
    for (int i = 0; i < n; ++i) {
        char ord;
        int val;
        std::cin >> ord >> val;
        if (ord == '+') {
            node.upd(val, val);
        } else {
            std::cout << node.query(0, val) << '\n';
        }
    }
}