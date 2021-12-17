#include <iostream>

class segTree {
    int *tree;
private:
    int min(int a, int b) { return (a > b) ? b : a; };

    int max(int a, int b) { return (a > b) ? a : b; };

    int reqPowT(int x) {
        int ans = 1;
        while (x != 1) {
            x /= 2;
            ans *= 2;
        }
        return ans * 2;
    }

public:
    segTree(int n);

    void update(int v, int tl, int tr, int pos, int delta);

    int getSum(int v, int tl, int tr, int l, int r, int bl, int br);

    void priint(int n){
        std::cout << "tree: ";
        for(int i = 0 ; i < n; i++){
            std::cout << *(tree + i) << " ";
        }
        std::cout << " done\n";
    }
};

segTree::segTree(int n) {
    tree = new int[4 * n + 1];
}


void segTree::update(int v, int tl, int tr, int pos, int delta) {
    if (tl == tr) {
        *(tree + v) = delta;
        return;
    }
    int tm = (tl + tr) >> 1;
    int sign = ((tm + 1 - tl) % 2 ? -1 : 1);

    if (pos <= tm) {
        update(2 * v, tl, tm, pos, delta);
    } else {
        update(2 * v + 1, tm + 1, tr, pos, delta);
    }
    *(tree + v) = *(tree + v * 2) + *(tree + v * 2 + 1) * sign;
}

int segTree::getSum(int v, int tl, int tr, int l, int r, int bl, int br) {
    if (tl == l && tr == r) {
        int sign = (bl == l ? 1 :((bl - l) % 2 ? -1 : 1));
        return *(tree + v) * sign;
    }
    int tm = (tl + tr) >> 1;
    int ans = 0;
    int start = tm + 1;
    if (l <= tm){
        ans += getSum(2 * v, tl, tm, l, min(r, tm), bl, br);
    }
    if (r >= tm + 1) {
        ans += getSum(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, bl, br);
    }
    return ans;
}

int main() {
    int n;
    std::cin >> n;
    int a[n];
    segTree seg(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        int sign = (i % 2 ? -1 : 1);
        seg.update(1, 0, n - 1, i, a[i]);
    }
    int k;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        int ord, l, r;
        std::cin >> ord >> l >> r;
        --l;
        if (ord == 0) {
            seg.update(1, 0, n - 1, l, r);
            a[l] = r;
        } else if (ord == 1) {
            --r;
            std::cout << seg.getSum(1, 0, n - 1, l, r, l, r) << '\n';
        }
    }
    return 0;
}
