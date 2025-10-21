#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

long long total_swaps;

int partition(vector<int> &a, int p, int r) {
    int pivot_val = a[(p + r) / 2];

    // 2. Find all candidate indices for i (from left) and j (from right)
    vector<int> i_candidates;
    for (int i = p; i <= r; ++i) {
        if (a[i] >= pivot_val) {
            i_candidates.push_back(i);
        }
    }
    vector<int> j_candidates;
    for (int j = r; j >= p; --j) {
        if (a[j] <= pivot_val) {
            j_candidates.push_back(j);
        }
    }

    // bool inA = find(i_candidates.begin(), i_candidates.end(), pivot_val) != i_candidates.end();

    // bool inB = find(j_candidates.begin(), j_candidates.end(), pivot_val) != j_candidates.end();

    // if (inA && inB) {

    // i_candidates.erase(remove(i_candidates.begin(), i_candidates.end(), pivot_val), i_candidates.end());

    // j_candidates.erase(remove(j_candidates.begin(), j_candidates.end(), pivot_val), j_candidates.end());

    // } 
    int current_swaps = 0;
    int num_pairs = min(i_candidates.size(), j_candidates.size());
    int q = -1;
    for (int k = 0; k < num_pairs; ++k) {
        int i = i_candidates[k];
        int j = j_candidates[k];

        if (i >= j) {
            q = j;
            break; // Pointers have crossed, no more swaps in this partition
        }
        
        current_swaps++;
        swap(a[i], a[j]);
    }
    total_swaps += current_swaps;

    if(q == -1){
        if( j_candidates.size() > num_pairs){
            q = j_candidates[num_pairs];
        }else{
            q = i_candidates[num_pairs - 1];
        }
    }
    
    for(int i:a){
        cout << i << " ";
    }
    cout << total_swaps;
    cout << "\n";
    return q;
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
