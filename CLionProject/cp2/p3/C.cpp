#include <iostream>

int QuickSelect(int *arr, int l, int r, int k) {
    std::swap(arr[(l+r)/2], arr[r]);
    int x = arr[r], i = l - 1;
    for(int j = l; j <= r; j++){
        if(arr[j] < x) {
            std::swap(arr[++i], arr[j]);
        }
    }
    std::swap(arr[++i], arr[r]);
    if(i - l == k - 1) return arr[i];
    if(i - l > k - 1) return QuickSelect(arr, l, i - 1, k);
    return QuickSelect(arr, i + 1, r, k - i + l - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    int a[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::cout << QuickSelect(a, 0, n - 1, k + 1);
}
