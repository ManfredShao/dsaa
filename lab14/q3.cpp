#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)

int scc_cnt=0, timer = 0;
int n,m;
int maxn = 1e6 + 5;
vector<vector<int>> adj(maxn);
vector<int> dfn(maxn);
vector<int> low(maxn);
vector<int> scc(maxn);
vector<bool> in_stack(maxn);
stack<int> st;

int getVal(int x){
    if(x>0) return x;
    else return -x+n;
}

int getNeg(int x){
    if(x > n) return x-n;
    else return x+n;
}

void tarjan(int u){
    timer++;
    dfn[u]=low[u]=timer;
    st.push(u);
    in_stack[u] = true;
    for(int v:adj[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[v],low[u]);
        }
        else if(in_stack[v]){
            low[u] = min(low[v],dfn[v]);
        }
    }
    if(dfn[u] == low[u]){
        scc_cnt++;
        int v;
        do{
            v = st.top();
            st.pop();
            in_stack[v] = false;
            scc[v] = scc_cnt;
        }while(u!=v);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string p,cnf;
    cin >> p >> cnf >> n >> m;
    rep(i,0,m-1){
        int a,b,zero;
        cin >> a >> b >> zero;
        int x = getVal(a);
        int y = getVal(b);
        adj[getNeg(x)].push_back(y);
        adj[getNeg(y)].push_back(x);
    }
    rep(i,1,2*n){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    rep(i,1,n){
        if(scc[i] == scc[i+n]){
            cout << "s UNSATISFIABLE" << endl;
            return 0;            
        }
    }

    cout << "s SATISFIABLE" << endl;
    cout << 'v' << ' ';
    rep(i,1,n){
        if(scc[i] < scc[i+n]){
            cout << i << ' ';
        }else{
            cout << -i << ' ';
        }
    }
    cout << 0 << endl;
    return 0;
}