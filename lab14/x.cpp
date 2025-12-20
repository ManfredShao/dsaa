#include <iostream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

const int MAXN = 250;
int n, m;

// adj: 原图, rev_adj: 反图（边方向取反）
bitset<MAXN> adj[MAXN];
bitset<MAXN> rev_adj[MAXN];
bitset<MAXN> vis; // 访问标记
int stk[MAXN], top = 0; // 手写栈，用于存储拓扑序

// 第一遍 DFS：确定拓扑序（结束时间）
void dfs1(int u) {
    vis[u] = 1;
    // 利用 bitset 快速找下一个未访问的邻居
    // adj[u] 是 u 的所有邻居，~vis 是所有未访问的点
    // 按位与后得到 u 的所有未访问邻居
    bitset<MAXN> next_nodes = adj[u] & ~vis;
    
    // _Find_first() 和 _Find_next() 是 bitset 的高效查找函数
    for (int v = next_nodes._Find_first(); v < MAXN; v = next_nodes._Find_next(v)) {
        dfs1(v);
        // 注意：dfs1回来后 vis 可能变了，为了保险重新计算或依靠递归本身逻辑
        // 其实这里的 bitset 优化查找在递归中稍微麻烦，
        // 简单写法是直接循环，虽然稍微慢点但也能过，下面演示最稳妥的直接循环写法配合位运算优化
        // 为了代码简洁和避免递归层级问题，这里还是用常规逻辑配合 bitset 加速判断
    }
    stk[top++] = u;
}

// 优化版的 dfs1，不依赖 bitset 内部函数，避免不同编译器差异
void dfs1_simple(int u) {
    vis[u] = 1;
    for (int v = 0; v < n; ++v) {
        // adj[u][v] 为 1 且没有访问过
        if (adj[u][v] && !vis[v]) {
            dfs1_simple(v);
        }
    }
    stk[top++] = u;
}

// 第二遍 DFS：在反图上把连通块揪出来
int dfs2(int u) {
    vis[u] = 1;
    int size = 1;
    // 在反图上找邻居
    bitset<MAXN> next_nodes = rev_adj[u] & ~vis;
    for (int v = next_nodes._Find_first(); v < MAXN; v = next_nodes._Find_next(v)) {
        size += dfs2(v);
    }
    return size;
}

// 既然 N 很小 (250)，我们可以用简单的循环配合 bitset 判断来写 dfs2，防止出错
int dfs2_simple(int u) {
    vis[u] = 1;
    int size = 1;
    for (int v = 0; v < n; ++v) {
        if (rev_adj[u][v] && !vis[v]) {
            size += dfs2_simple(v);
        }
    }
    return size;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                adj[i][j] = 1;
                rev_adj[j][i] = 1; // 同时构建反图
            }
        }
    }

    for (int k = 0; k < m; k++) {
        int changes;
        cin >> changes;
        while (changes--) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            // 翻转边，同时维护原图和反图
            adj[u].flip(v);
            rev_adj[v].flip(u);
        }

        // --- Kosaraju 算法开始 ---
        
        // 1. 第一遍 DFS，计算后序遍历
        vis.reset();
        top = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) dfs1_simple(i);
        }

        // 2. 第二遍 DFS，在反图上按逆后序遍历
        vis.reset();
        long long ans = 0;
        // 栈中取出节点（相当于时间戳从大到小）
        while (top > 0) {
            int u = stk[--top];
            if (!vis[u]) {
                int size = dfs2_simple(u); // 找出一个 SCC 的大小
                // 计算 C(size, 2)
                ans += (long long)size * (size - 1) / 2;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}