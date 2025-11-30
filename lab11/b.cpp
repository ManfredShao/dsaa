#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(2*n+1), prefix_sum(2*n+1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    prefix_sum[0] = 0;
    for(int i = 1; i <= 2*n; i++) {
        prefix_sum[i] = prefix_sum[i-1] + a[i];
    }

    int dp_min[2*n+1][2*n+1];
    int dp_max[2*n+1][2*n+1];
    for(int i=1; i<=2*n; i++){
        for(int j=1; j<=2*n; j++){
            if(i==j){
                dp_min[i][j] = 0;
                dp_max[i][j] = 0;
            }else{
                dp_min[i][j] = INT_MAX;
                dp_max[i][j] = 0;    
            }
        }
    }

    for(int len=2; len <=n; len++){
        for(int i=1; i<=2*n - len + 1; i++){
            int j = i + len -1;
            int sum = prefix_sum[j] - prefix_sum[i-1];
            for(int k=i; k<j; k++){
                dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k+1][j] + sum);
                dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k+1][j] + sum);
            }
        }
    }
    int min_result = INT_MAX;
    int max_result = 0;
    for(int i=1; i<=n; i++){
        min_result = min(min_result, dp_min[i][i+n-1]);
        max_result = max(max_result, dp_max[i][i+n-1]);
    }
    cout << min_result << endl;
    cout << max_result << endl;
    return 0;
}