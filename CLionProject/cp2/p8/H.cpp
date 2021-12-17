#include <iostream>

void lsd(long long *arr, int n) {
    for (long long i = 0; i < 16; i++) {
        long long temp_arr[n];
        int cnt[16];
        for (int j = 0; j < 16; j++) { //all zeroes
            cnt[j] = 0;
        }
        for (int j = 0; j < n; j++) { //start of counting sort
            int d = (arr[j] & (15LL << i * 4)) >> (i * 4);
            ++cnt[d];
        }
        int curr = 0;
        for (int j = 0; j < 16; j++) { //start of intervals
            int tmp = cnt[j];
            cnt[j] = curr;
            curr += tmp;
        }
        for (int j = 0; j < n; j++) { //
            int d = (arr[j] & (15LL << i * 4)) >> (i * 4);
            int k = cnt[d];
            temp_arr[k] = arr[j];
            ++cnt[d];
        }
        for (int j = 0; j < n; j++) {
            arr[j] = temp_arr[j];
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    long long arr[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    long long temp_arr[n];
    for (long long i = 0; i < 16; i++) {
        int cnt[16] = {0};
        for (int j = 0; j < n; j++) { //start of counting sort
            ++cnt[(arr[j] & (15LL << i * 4)) >> (i * 4)];
        }
        int curr = 0;
        for (int j = 0; j < 16; j++) { //start of intervals
            int tmp = cnt[j];
            cnt[j] = curr;
            curr += tmp;
        }
        for (int j = 0; j < n; j++) { //
            int d = (arr[j] & (15LL << i * 4)) >> (i * 4);
            temp_arr[cnt[d]] = arr[j];
            ++cnt[d];
        }
        for (int j = 0; j < n; j++) {
            arr[j] = temp_arr[j];
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
}