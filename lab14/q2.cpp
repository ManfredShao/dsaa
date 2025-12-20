#pragma GCC optimize("O3") // 开启编译器优化
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

#define rep(i,a,b) for(int i=a;i<=b;i++)

const int MAXN = 250;
int n, m;
bitset<MAXN> adj[MAXN];
bitset<MAXN> rev_adj[MAXN];
bitset<MAXN> vis;
int st[MAXN];
int top = 0;

void dfs1(int u){
    vis[u] = 1;
    // 使用 while 循环配合动态位运算。
    // 每次递归回来后，vis 发生了变化，(adj[u] & ~vis) 会自动过滤掉那些在递归过程中已经被访问的节点。
    while(true) {
        // _Find_first 直接跳到下一个“真正的”未访问邻居
        int v = (adj[u] & ~vis)._Find_first();
        if(v >= MAXN) break; 
        dfs1(v);
    }
    st[top++] = u;
}

int dfs2(int u){
    vis[u] = 1;
    int size = 1;
    // dfs2 同理优化
    while(true) {
        int v = (rev_adj[u] & ~vis)._Find_first();
        if(v >= MAXN) break;
        size += dfs2(v);
    }
    return size;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    if(!(cin >> n >> m)) return 0;

    rep(i,0,n-1){
        string s;
        cin >> s;
        rep(j,0,n-1){
            if(s[j] == '1') {
                adj[i][j] = 1;
                rev_adj[j][i] = 1;
            }
        }
    }    
    
    rep(i,0,m-1){
        int k;
        cin >> k;
        while(k--){
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].flip(v);
            rev_adj[v].flip(u);
        }

        // 第一遍 DFS：算拓扑序
        vis.reset();
        top = 0;
        rep(u,0,n-1){
            if(!vis[u]){
                dfs1(u);
            }
        }

        // 第二遍 DFS：算 SCC 大小
        vis.reset();
        long long cnt = 0;
        while(top > 0){
            int u = st[--top];
            if(!vis[u]){
                int size = dfs2(u);
                // 循环对数 = C(size, 2)
                cnt += (long long) size * (size-1) / 2 ;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}