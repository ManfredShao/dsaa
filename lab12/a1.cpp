#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

int main() {
    int n;
    long long s;
    cin >> n >> s;
    deque<long long> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    if(s == 1) return 1;
    else if(s == 2){
        if(n == 1) return 1;
        else return 2;
    }
    else{
        long long res = 2;
        arr.pop_back();
        arr.pop_back();
        int i = 0;
        while(i < n-2 && res < s){
            if(arr[i] % 3 == 0){
                res++;
                arr.pop_front();
            }
            else{
                if(i=n-3) 
                if(i+1 < n-2 && (arr[i]+arr[i+1]) % 3 == 0){
                    res++;
                    arr.pop_front();
                    arr.pop_front();
                    i++;
                }
                else{

                }
            }
        }
    }
    return 0;
}