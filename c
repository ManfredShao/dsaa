#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long total_swaps;

int partition(vector<int> &a, int p, int r) {
    int pivot_val = a[(p + r) / 2];
    int i = p - 1;
    int j = r + 1;
    
    while (true) {
        // Move i to the right while a[i] < pivot
        do {
            i++;
        } while (a[i] < pivot_val);
        
        // Move j to the left while a[j] > pivot
        do {
            j--;
        } while (a[j] > pivot_val);
        
        // If pointers crossed, return partition point
        if (i >= j) {
            return j;
        }
        
        // Swap elements and count the swap
        swap(a[i], a[j]);
        total_swaps++;
    }
}

void quickSort(vector<int> &a, int p, int r) {
    if (p < r) {
        int q = partition(a, p, r);
        quickSort(a, p, q);
        quickSort(a, q + 1, r);
    }
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

        total_swaps = 0;
        if (n > 0) {
            quickSort(a, 0, n - 1);
        }
        cout << total_swaps << endl;
    }
    return 0;
}
