#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct Group {
    int c; // count
    int f; // floor
};

void solve() {
    int n;
    ll k;
    if (!(cin >> n >> k)) return;

    vector<Group> ones, twos;
    for (int i = 0; i < n; i++) {
        int c, w, f;
        cin >> c >> w >> f;
        if (w == 1) {
            ones.push_back({c, f});
        } else {
            twos.push_back({c, f});
        }
    }

    // 按楼层升序排序，方便后续取最高楼层
    auto comp = [](const Group& a, const Group& b) {
        return a.f < b.f;
    };
    sort(ones.begin(), ones.end(), comp);
    sort(twos.begin(), twos.end(), comp);

    ll total_cost = 0;

    // 当还有货物未运送时
    while (!ones.empty() || !twos.empty()) {
        int h1 = ones.empty() ? 0 : ones.back().f;
        int h2 = twos.empty() ? 0 : twos.back().f;

        // 当前趟的成本由最高楼层决定
        int current_f = max(h1, h2);
        
        // 决定由哪一组发起运输（Peak）
        // 如果楼层一样，优先处理重量为2的，保留重量为1的以备填补奇数空隙
        if (h2 >= h1) {
            // 处理重量为2的组
            Group &g = twos.back();
            ll items_per_ride = k / 2; // k是偶数，正好除尽
            ll rides = g.c / items_per_ride;
            
            // 批量计算满载行程
            total_cost += rides * current_f;
            g.c %= items_per_ride;

            if (g.c == 0) {
                twos.pop_back(); // 该组运完了
            } else {
                // 还有剩余，需要一次非满载行程，并尝试填缝
                total_cost += current_f;
                ll rem_cap = k - (g.c * 2);
                twos.pop_back(); // 主导组已清空（剩余部分上了这趟车）

                // 贪心填补剩余空间
                while (rem_cap > 0 && (!ones.empty() || !twos.empty())) {
                    int ph1 = ones.empty() ? 0 : ones.back().f;
                    int ph2 = twos.empty() ? 0 : twos.back().f;

                    // 优先拿楼层高的；楼层相同优先拿重量2的
                    if (ph2 >= ph1) {
                        if (rem_cap >= 2) {
                            ll take = min((ll)twos.back().c, rem_cap / 2);
                            twos.back().c -= take;
                            rem_cap -= take * 2;
                            if (twos.back().c == 0) twos.pop_back();
                        } else {
                            // 空间只剩1，不能拿重量2的，尝试拿重量1的
                            if (!ones.empty()) {
                                ones.back().c--;
                                rem_cap--;
                                if (ones.back().c == 0) ones.pop_back();
                            } else {
                                break; // 没得填了
                            }
                        }
                    } else {
                        // 拿重量1的
                        ll take = min((ll)ones.back().c, rem_cap);
                        ones.back().c -= take;
                        rem_cap -= take;
                        if (ones.back().c == 0) ones.pop_back();
                    }
                }
            }
        } else {
            // 处理重量为1的组 
            Group &g = ones.back();
            ll items_per_ride = k;
            ll rides = g.c / items_per_ride;

            total_cost += rides * current_f;
            g.c %= items_per_ride;

            if (g.c == 0) {
                ones.pop_back();
            } else {
                total_cost += current_f;
                ll rem_cap = k - g.c;
                ones.pop_back();

                while (rem_cap > 0 && (!ones.empty() || !twos.empty())) {
                    int ph1 = ones.empty() ? 0 : ones.back().f;
                    int ph2 = twos.empty() ? 0 : twos.back().f;

                    if (ph2 >= ph1) {
                        if (rem_cap >= 2) {
                            ll take = min((ll)twos.back().c, rem_cap / 2);
                            twos.back().c -= take;
                            rem_cap -= take * 2;
                            if (twos.back().c == 0) twos.pop_back();
                        } else {
                            if (!ones.empty()) {
                                ones.back().c--;
                                rem_cap--;
                                if (ones.back().c == 0) ones.pop_back();
                            } else {
                                break;
                            }
                        }
                    } else {
                        ll take = min((ll)ones.back().c, rem_cap);
                        ones.back().c -= take;
                        rem_cap -= take;
                        if (ones.back().c == 0) ones.pop_back();
                    }
                }
            }
        }
    }
    cout << total_cost << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}