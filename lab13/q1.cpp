#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct edge{
    int u;
    int v;
};

int bfs(int start, int end, const vector<edge>& edges, int n){
    vector<vector<int>> graph(n+1);
    vector<vector<int>> re_graph(n+1);
    for(const auto& e:edges){
        re_graph[e.v].push_back(e.u);
        graph[e.u].push_back(e.v);
    }

    // 步骤1：反向BFS找出所有能到达终点的节点
    vector<bool> can_reach_end(n+1, false);
    queue<int> q;
    q.push(end);
    can_reach_end[end] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : re_graph[u]){
            if(!can_reach_end[v]){
                can_reach_end[v] = true;
                q.push(v);
            }
        }
    }

    // 步骤2：找出所有只能通向终点的节点
    vector<bool> valid(n+1,false);
    for(int u=1; u<=n; u++){
        if(u == end) {
            valid[u] = true;
            continue;
        }
        if(graph[u].empty()){
            continue;
        }
        bool all_good = true;
        for(int v: graph[u]){
            if(!can_reach_end[v]){
                all_good = false;
                break;
            }
        }
        valid[u] = all_good;
    }

    if(!valid[start]) return -1;

    vector<int> d(n+1,-1);
    queue<int> q2;
    q2.push(start);
    d[start] = 0;

    while(!q2.empty()){
        int u = q2.front();
        q2.pop();
        for(int v: graph[u]){
            if(d[v] == -1 && valid[v]){
                d[v] = d[u] + 1;
                q2.push(v);
                if(v == end) return d[v];
            }
        }
    }
    return d[end];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    vector<edge> edges(m);
    for(int i = 0; i < m; i++){
        cin >> edges[i].u >> edges[i].v;
    }
    int start;
    int end;
    cin >> start >> end;
    int len = bfs(start, end, edges, n);
    cout << len << "\n";
    return 0;
}