#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
const long long INF = 1e18;
const int MAXN = 500005;
#define rep(i,a,b)  for(int i=a;i<=b;i++)

struct edge
{
    int to;
    ll w;
};

vector<edge> adj[MAXN];
ll dist[MAXN];
int parent[MAXN];

struct IndexedMinHeap
{
    int heap[MAXN];
    int pos[MAXN];
    int size;
    IndexedMinHeap(){
        size = 0;
        rep(i,0,MAXN-1){
            pos[i] = -1;
        }
    }

    void push(int v){
        size++;
        pos[v] = size;
        heap[size] = v;
        sift_up(size);
    }

    void sift_up(int idx){
        while(idx > 1 && dist[heap[idx]] < dist[heap[idx/2]]){
            swap_node(idx,idx/2);
            idx = idx/2;
        }
    }

void sift_down(int idx){
    while(2*idx <= size){
        int left = 2*idx;
        int right = 2*idx+1;
        int smallest = left;
        if(right <= size && dist[heap[left]] > dist[heap[right]]){
            smallest = right;
        }
        if(dist[heap[smallest]] < dist[heap[idx]]){
            swap_node(smallest,idx);
            idx = smallest;
        }else{
            break;
        }
    }
}

    void swap_node(int a,int b){
        int u = heap[a];
        int v = heap[b];
        swap(heap[a],heap[b]);
        pos[u] = b;
        pos[v] = a;
    }

    int pop(){
        int min_node = heap[1];
        swap_node(1,size);
        size--;
        pos[min_node] = -1;
        if(size > 1){
            sift_down(1);
        }
        return min_node;
    }

    void decrease_key(int v){
        if(pos[v]!=-1){
            sift_up(pos[v]);
        }
    }

    bool empty(){
        return size == 0;
    }

}minHeap;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,s,t;
    cin >> n >>m >> s >> t;
    rep(i,0,m-1){
        int a,b;
        ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
    }
    rep(i,0,n-1){
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[s] = 0;
    rep(i,0,n-1){
        minHeap.push(i);
    }
    while(!minHeap.empty()){
        int min_u = minHeap.pop();
        if(min_u == t) break;
        if(dist[min_u] == INF) break;

        for(edge& eg: adj[min_u]){
            int v = eg.to;
            ll w = eg.w;
            if(w + dist[min_u] < dist[v]){
                dist[v] = w + dist[min_u];
                parent[v] = min_u;
                minHeap.decrease_key(v);
            }
        }
    }

    if(dist[t] == INF) cout << -1 << endl;
    else{
        vector<pair<int,int>> path;
        int cur = t;
        while(cur != s){
            int p = parent[cur];
            path.push_back({p,cur});
            cur = p;
        }
        reverse(path.begin(), path.end());

        cout << dist[t] << " " << path.size() << endl;
        for(auto& p:path){
            cout << p.first << " " << p.second << endl;
        }
    }
    return 0;
}