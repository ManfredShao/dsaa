#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long s;
    if (!(cin >> n >> s)) return 0;

    vector<long long> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    sort(w.begin(), w.end());

    if(s == 1) {
        cout << 1 << endl;
        return 0;
    }
    else if(s == 2){
        if(n == 1) {
            cout << 1 << endl;
            return 0;
        }
        else{
            cout << 2 << endl;
            return 0;
        };
    }
    else{
        int count = 1;
        long long last_socket = 1;
        long long boundary = 3; 
    
        for (int i = 0; i < n-1; i++) {
            long long n_bound_l = boundary + w[i];
            long long n_socket_l = max(last_socket + 1,(long long)ceil((double)n_bound_l / 3.0)); 
            n_bound_l = n_socket_l * 3;
    
            bool valid_l = (n_socket_l <= s);
    
            long long n_bound_r = last_socket * 3 + w[i];
            long long n_socket_r = max(last_socket + 1,(long long)ceil((double)n_bound_r / 3.0)); 
    
            bool valid_r = (n_socket_r <= s);
    
            if(!valid_l && !valid_r) {
                break;
            }
    
            bool pick_l = false;
            if(valid_l && valid_r){
                if(n_socket_l < n_socket_r) pick_l = true;
                else if(n_socket_l > n_socket_r) {}
                else pick_l = (n_bound_l <= n_bound_r);
            }
            else pick_l = valid_l;
    
            if(pick_l){
                last_socket = n_socket_l;
                boundary = n_bound_l;
            }else{
                last_socket = n_socket_r;
                boundary = n_bound_r;            
            }
            count++;
        }
        
        cout << count << endl;
        return 0;
    }
}