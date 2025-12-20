#include <vector>
#include <iostream>

using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long ll;

struct edge
{
    int u,v;
    ll w;    
};

bool compareEdge(const edge& a,const edge& b){
    return a.w < b.w;
}

int parent[10020];
int find(int i){
    if(parent[i] == i) return i;
    return parent[i] = find(parent[i]); 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k;
    cin >> n >> m >> k;
    vector<edge> adj(m);
    rep(i,0,m-1){
        cin >> adj[i].u >> adj[i].v >> adj[i].w;
    }
    ll urban[k];
    rep(i,0,k-1){
        cin >> urban[i];
    }
    vector<edge> new_adj[n];
    rep(i,0,k-1){
        rep(j,0,n-1){
            ll a;
            cin >> a;
            new_adj[i].push_back({j,a});
        }
    }
    
    return 0;
}