#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
    int n,s;
    cin >> n >> s;
    vector<pair<int,int>> task(n);
    for(int i=0;i<n;i++){
        cin >> task[i].first >> task[i].second;
    }
    int dp[n+1];
    for(int i=0;i<n+1;i++){
        dp[i] = INT_MAX;
    }
    dp[0] = 0;

    int sumT[n+1];
    int sumC[n+1];
    for(int i=0;i<=n;i++){
        if(i==0){
            sumT[i] = 0;
            sumC[i] = 0;
        }else{
            sumT[i] = sumT[i-1] + task[i-1].first;
            sumC[i] = sumC[i-1] + task[i-1].second;
        }
    }

    for(int i=1;i<n+1;i++){
        for(int j=0;j<i;j++){
            dp[i] = min(dp[j] + (s + sumT[i] - sumT[j]) * (sumC[n] - sumC[j]), dp[i]);
        }
    }
    cout << dp[n] << endl;
    return 0;
}