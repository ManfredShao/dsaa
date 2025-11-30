#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string a,b;
    cin >> a >> b;
    int m = a.length();
    int n = b.length();
    int dp[m+1][n+1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0;j <= n; j++){
            dp[i][j] = 0;
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(a[i-1]==b[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = max (dp[i-1][j],dp[i][j-1]);
            }
        }
    }

    string lcs = "";
    while(m>0 && n>0){
        if(a[m-1]==b[n-1]){
            lcs += a[m-1];
            m--;
            n--;
        }else if(dp[m-1][n]>dp[m][n-1]){
            m--;
        }else{
            n--;
        }
    }
    reverse(lcs.begin(),lcs.end());
    cout << lcs << endl;
    return 0;
}