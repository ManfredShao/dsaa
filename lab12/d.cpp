#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;

struct group {
    ll l; 
    ll r; 
    int id;
};

struct pqitem{
    ll r;
    ll l;
    int id;
    bool operator <(const pqitem& other) const {
        return r < other.r;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n;
        ll f;
        cin >> n >> f;
        vector<group> arr(n);
        for(int i = 0; i < n; i++){
            cin >> arr[i].l >> arr[i].r;
            arr[i].id = i + 1;
        }
        auto comp = [](const group& a, const group& b) {
        return a.l < b.l;
        };
        sort(arr.begin(), arr.end(), comp);

        priority_queue<pqitem> pq;
        vector<int> order;
        order.reserve(n);

        ll cur = f;
        ll total_cost = 0;
        int ptr = 0;
        while(order.size() < n){
            while(ptr < n && cur >= arr[ptr].l){
            pq.push({arr[ptr].r, arr[ptr].l, arr[ptr].id});
                ptr++;
            }

            if(pq.empty()){
                if(ptr < n){
                    total_cost += arr[ptr].l - cur;
                    cur = arr[ptr].l;
                }
            }else{
                bool jump = false;
                pqitem u = pq.top();

                if(ptr < n){
                    ll jump_cost = arr[ptr].l - cur;
                    ll stay_cost = max(-u.r + arr[ptr].l, 0ll);
                    if(jump_cost <= stay_cost){
                        jump = true;
                        total_cost += jump_cost;
                        cur = arr[ptr].l;
                    }
                }

                if(!jump){
                    pq.pop();
                    total_cost += (u.r-u.l);
                    cur = u.r;
                    order.push_back(u.id);
                }
            }
        }

        cout << total_cost << "\n";
        for(int id : order){
            cout << id << " ";
        }
        cout << "\n";
    }
    return 0;
}