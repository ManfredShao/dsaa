#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 辅助函数：执行一次BFS
// start: 起点
// n: 节点总数
// graph: 邻接表
// 返回 pair: <最远节点的编号, 最远距离>
// 如果是从节点1开始调用的，可以用 visited_count 引用来检查连通性
pair<int, int> bfs(int start, int n, const vector<vector<int>>& graph, int& visited_count) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    
    q.push(start);
    dist[start] = 0;
    visited_count = 0;
    
    int max_dist = 0;
    int farthest_node = start;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited_count++;
        
        if (dist[u] > max_dist) {
            max_dist = dist[u];
            farthest_node = u;
        }
        
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return {farthest_node, max_dist};
}

int main() {
    // 开启 IO 优化，防止输入输出超时
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 如果只有一个点，直接0天
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 第一次 BFS：从节点 1 开始
    // 目的：1. 检查图是否连通 2. 找到最远端点 u
    int visited_count = 0;
    pair<int, int> p1 = bfs(1, n, graph, visited_count);
    
    // 如果访问到的节点数不等于 N，说明图不连通
    if (visited_count != n) {
        cout << -1 << endl;
        return 0;
    }

    int u = p1.first;

    // 第二次 BFS：从端点 u 开始
    // 目的：找到距离 u 最远的距离，即为直径
    int temp_count = 0;
    pair<int, int> p2 = bfs(u, n, graph, temp_count);
    
    int diam = p2.second;

    // 计算天数 ceil(log2(diam))
    // 注意：如果 diam 是 0 (例如 N=1 或孤立点，前面已处理)，log2(0) 会报错
    if (diam == 0) {
        cout << 0 << endl;
    } else {
        // 使用 ceil 和 log2 计算
        int day = ceil(log2((double)diam));
        cout << day << endl;
    }

    return 0;
}