#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct edge{
    int u,v;
};

pair<int,int> diameter(vector<vector<int>>& graph,int n,int start){
    int longest = 0;
    int far = 0;
        vector<int> d(n+1,-1);
        queue<int> q;
        q.push(start);
        d[start] = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int v: graph[u]){
                if(d[v] == -1){
                    q.push(v);
                    d[v] = d[u] + 1;
                    if(d[v] > longest){
                        longest = d[v];
                        far = v;
                    }
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(d[i] == -1){
                return {-1,0};
            }
        }
    return {longest,far};
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin >> n >> m;
    vector<edge> edges(m);
    for(int i=0; i<m; i++){
        int a,b;
        cin >> a >> b;
        edges[i].u = a;
        edges[i].v = b;
    }
    vector<vector<int>> graph(n+1);
    for(const auto& e:edges){
        graph[e.u].push_back(e.v);
        graph[e.v].push_back(e.u);
    }
    pair<int,int> p1 = diameter(graph,n,1);

    if(p1.first == -1){
        cout << -1 << endl;
        return 0;
    }
    int u = p1.second;
    pair<int,int> p2 = diameter(graph,n,u);
    int day = ceil(log2(p2.first));
    cout << day << endl;
    return 0;
}