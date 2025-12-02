#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;

struct Group {
    ll l, r;
    int id;
};

// 按起始楼层 l 升序排序
bool cmp(const Group& a, const Group& b) {
    return a.l < b.l;
}

struct PqItem {
    ll r, l;
    int id;
    // 大根堆：目的楼层 r 大的优先
    bool operator<(const PqItem& other) const {
        return r < other.r;
    }
};

void solve() {
    int n;
    ll f;
    cin >> n >> f;
    vector<Group> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i].l >> arr[i].r;
        arr[i].id = i + 1;
    }

    // 按起始楼层排序
    sort(arr.begin(), arr.end(), cmp);

    priority_queue<PqItem> pq;  // 候选池：当前可服务的人
    vector<int> ans;            // 服务顺序

    ll cur = f;     // 电梯当前位置
    ll cost = 0;    // 总能量消耗
    int idx = 0;    // 下一个待加入候选池的人

    while (ans.size() < n) {
        // 将所有起始楼层 <= 当前位置的人加入候选池（下降免费）
        while (idx < n && arr[idx].l <= cur) {
            pq.push({arr[idx].r, arr[idx].l, arr[idx].id});
            idx++;
        }

        if (pq.empty()) {
            // 候选池为空，必须上升去接人
            // 选择起始楼层最低的人（已按 l 排序，即 arr[idx]）
            if (idx < n) {
                cost += (arr[idx].l - cur);  // 空载上升消耗能量
                cur = arr[idx].l;
            }
        } else {
            // 候选池非空，取目的楼层最高的人
            PqItem u = pq.top();
            
            // 判断：是否应该跳过当前候选，先去接上面的人？
            bool should_jump = false;
            
            if (idx < n) {
                ll next_l = arr[idx].l;  // 上方最近的人的起始楼层
                
                // 方案1代价：直接上升到 next_l
                ll jump_cost = next_l - cur;
                
                // 方案2代价：先送 u 到 u.r，再从 u.r 上升到 next_l
                ll stay_cost = max(0LL, next_l - u.r);
                
                // 若直接跳上去更省，则跳过当前候选
                if (jump_cost < stay_cost) {
                    should_jump = true;
                    cost += jump_cost;
                    cur = next_l;
                    // u 仍在候选池中，下轮可能被选中
                }
            }
            
            if (!should_jump) {
                // 服务当前候选人 u
                pq.pop();
                cost += (u.r - u.l);    // 载客上升消耗能量
                cur = u.r;              // 更新电梯位置
                ans.push_back(u.id);
            }
        }
    }

    cout << cost << "\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}