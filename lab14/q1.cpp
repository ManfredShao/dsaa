#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef __int128_t int128;
// 输出 int128
void print_int128(int128 x){
    if(x == 0){
        cout << 0;
        return;
    }
    string s;
    while(x > 0){
        s = char('0' + x % 10) + s;
        x /= 10;
    }
    cout << s;
}

int128 gcd(int128 a, int128 b){
    while(b){
        int128 t = b;
        b = a % b;
        a = t;
    }
    return a;
}

struct Fraction
{
    /* data */
    int128 p,q; // p/q
    Fraction(int128 _p = 0, int128 _q = 1) : p(_p), q(_q){
        simplify();
    }

    void simplify(){
        if(p == 0){
            q = 1;
            return;
        }
        int128 g = gcd(p,q);
        p /= g;
        q /= g;
    }

    Fraction operator+(const Fraction& other) const{
        int128 g = gcd(q,other.q);
        int128 new_q = q / g * other.q;
        int128 new_p = p * (new_q / q) + other.p * (new_q / other.q);
        return Fraction(new_p, new_q);
    }
    Fraction operator/(int128 k) const{
        int128 g = gcd(p, k);
        return Fraction(p / g, q * (k / g));
    }
};

void dfs_visit(vector<vector<int>>& graph, list<int>& topo, int u, vector<bool>& visited){
    visited[u] = true;
    for(int& v: graph[u]){
        if(!visited[v]){
            dfs_visit(graph,topo,v,visited);
        }
    }
    topo.push_front(u);
}

list<int> dfs(vector<vector<int>>& graph, int n){
    vector<bool> visited(n+1,false);
    list<int> topo;
    for(int i=1; i<=n; i++){
        if(!visited[i]){
            dfs_visit(graph, topo, i, visited);
        }
    }
    return topo;
}   

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1);
    vector<bool> entry(n+1,true);
    entry[0] = false;
    for(int i=1; i<=n; i++){
        int a;
        cin >> a;
        for(int j=0; j<a; j++) {
            int b;
            cin >> b;
            graph[i].push_back(b);
            entry[b] = false;
        }
    }
    vector<Fraction> mount(n+1);
    list<int> topo = dfs(graph, n);
    for(int i=1;i<=n;i++){
        if(entry[i] == true){
            mount[i] = Fraction(1,1);
        }
    }
    // 按拓扑序处理每个节点
    for(int u : topo){
        if(graph[u].size() > 0){  // 有出边，分配污水
            Fraction share = mount[u] / (int128) graph[u].size();
            for(int v : graph[u]){
                mount[v] = mount[v] + share;
            }
        }
        // 没有出边的节点保留污水量（出口节点）
    }
    
    for(int i = 1; i <= n; i++){
        if(graph[i].empty()){  // 出口节点
            print_int128(mount[i].p);
            cout << " ";
            print_int128(mount[i].q);
            cout << "\n";    
        }
    }
    return 0;
}