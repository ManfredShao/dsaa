#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long countSwapsInPartition(vector<int>& a, int p, int r, int& partition_point) {
    int pivot_val = a[(p + r) / 2];
    int i = p - 1;
    int j = r + 1;
    long long swaps = 0;
    
    while (true) {
        do { i++; } while (a[i] < pivot_val);
        do { j--; } while (a[j] > pivot_val);
        
        if (i >= j) {
            partition_point = j;
            return swaps;
        }
        
        swap(a[i], a[j]);
        swaps++;
    }
}

long long quickSortCount(vector<int>& a, int p, int r) {
    if (p >= r) return 0;
    
    int q;
    long long swaps = countSwapsInPartition(a, p, r, q);
    
    swaps += quickSortCount(a, p, q);
    swaps += quickSortCount(a, q + 1, r);
    
    return swaps;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        long long result = 0;
        if (n > 0) {
            result = quickSortCount(a, 0, n - 1);
        }
        cout << result << endl;
    }
    return 0;
}
