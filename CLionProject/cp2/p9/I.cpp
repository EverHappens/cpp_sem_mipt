#include <iostream>

void QuickSort(int *arr, int l, int r) {
    int left = l, right = r, pivot = arr[(l+r)/2];
    while(left <= right){
        while(arr[left] < pivot) ++left;
        while(arr[right] > pivot) --right;
        if(left <= right){
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
    if(right > l) QuickSort(arr, l, right);
    if(left < r) QuickSort(arr, left, r);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    QuickSort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    return 0;
}