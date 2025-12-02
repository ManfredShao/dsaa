#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll nItems, totalSpace;
    cin >> nItems >> totalSpace;

    vector<ll> weight(nItems);
    for (int i = 0; i < nItems; i++) cin >> weight[i];

    if (totalSpace == 1) { 
        cout << 1 << "\n"; 
        return 0; 
    }

    if (nItems == 1) {
        cout << 1 << "\n";
        return 0;
    }

    if (nItems == 2) {
        cout << (totalSpace >= 2 ? 2 : 1) << "\n";
        return 0;
    }

    sort(weight.begin(), weight.end());

    ll freeSlots = totalSpace - 2;
    ll used = 2;

    // 累计 floor(w/3)
    ll sumBase = 0;

    // 记录余数统计
    ll rem1 = 0, rem2 = 0;

    for (int i = 0; i < nItems - 2; i++) {
        sumBase += weight[i] / 3;
        int r = weight[i] % 3;
        if (r == 1) rem1++;
        else if (r == 2) rem2++;

        // 贪心配对
        ll pair12 = min(rem1, rem2);
        ll left1 = rem1 - pair12;
        ll pair11 = left1 / 2;

        ll reduced = pair12 + pair11;
        ll extra = (rem1 + rem2) - reduced;

        ll need = sumBase + extra;

        if (need <= freeSlots) used++;
        else break;
    }

    cout << used << "\n";
    return 0;
}
