#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

ll cal (ll k, int i, vector<pair<pair<int,int>,int>> &parcel){
    ll sum = 0;
    if(i >= parcel.size()) return 0;
    ll afford = k ;
    sum += ll(parcel[i].second);

        while(i<parcel.size() && afford > 0){
               if(afford >= parcel[i].first.first*parcel[i].first.second){
                    afford -= parcel[i].first.first * parcel[i].first.second;
                    parcel[i].first.first = 0;
                    i++;
                }
               else{
                    if(afford % parcel[i].first.second == 0){
                        parcel[i].first.first -= afford / parcel[i].first.second;
                    }
                    else{
                        parcel[i].first.first -= afford / parcel[i].first.second;
                        for(int j=i;j<parcel.size();j++){
                            if(parcel[j].first.second == 1){
                                parcel[j].first.first -= 1;
                                break;
                            }
                        }
                    }
                    sum += cal(k,i,parcel);
                }
        }

    return sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n;
        ll k;
        cin >> n >> k;
        vector<pair<pair<int,int>,int>> parcel(n);
        for(int i=0;i<n;i++){
            cin >> parcel[i].first.first //c
                >> parcel[i].first.second //w
                >> parcel[i].second; //f
        }
        //根据f从大到小排序
        sort(parcel.begin(),parcel.end(),[](const auto &a,const auto &b){
            return a.second > b.second;
        });

        ll total = 0;

        total = cal(k,0,parcel);
        
        cout << total << endl;
    }
    return 0;
}