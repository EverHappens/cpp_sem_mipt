#include <iostream>
#include <vector>

class SparseTable {
    std::vector<std::vector<std::pair<int, int>>> sparse; // 2^k and position of begin

private:
    int bspt(int x) {
        if (x == 0) return 0;
        int k = 0;
        while (x > 1) {
            x /= 2;
            k++;
        }
        return k;
    }

public:
    SparseTable(int n);

    void build(int a[], int n);

    int getMin(int l, int r);

    int getSecMin(int l, int r);
};

SparseTable::SparseTable(int n) {
    int k = bspt(n) + 5;
    sparse = std::vector<std::vector<std::pair<int, int>>>(k, std::vector<std::pair<int, int>>(n, {0, 0}));
}

void SparseTable::build(int a[], int n) {
    int k = bspt(n);
    for (int i = 0; i < n; i++) {
        sparse[0][i].first = a[i];
        sparse[0][i].second = i;
    }
    for (int l = 0; l < k; l++) {
        for (int i = 0; i + (2 << l) <= n; i++) {
            sparse[l + 1][i] = min(sparse[l][i], sparse[l][i + (1 << l)]);
        }
    }
}

int SparseTable::getMin(int l, int r) {
    int k = bspt(r - l);
    int m = std::min(sparse[k][l], sparse[k][r - (1 << k)]).second;
    if (m == l) return getSecMin(l + 1, r);
    if (m == r - 1) return getSecMin(l, r - 1);
    return std::min(getSecMin(l, m), getSecMin(m + 1, r));
}

int SparseTable::getSecMin(int l, int r) {
    int k = bspt(r - l);
    return std::min(sparse[k][l], sparse[k][r - (1 << k)]).first;

}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    long long n, k;
    std::cin >> n >> k;
    SparseTable sparse(n);
    int a[n];
    for (long long i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    sparse.build(a, n);
    for (long long i = 0; i < k; i++) {
        long long l, r;
        std::cin >> l >> r;
        std::cout << sparse.getMin(l - 1, r) << '\n';
    }
    return 0;
}
