#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define ppii pair<int,pii>
#define pb push_back
#define p push
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
//#define int long long
const int mxn=2*1e5,mod=29947,lg=30;
vector<pii>adj[mxn+10],e,adj2[mxn+10];
int low[mxn+10],g[mxn+10],id[mxn+10];
int up[mxn+10][lg+10],h[mxn+10],ans[mxn+10];
pii info[mxn+10];
stack<int>st;
bitset<mxn+10>on;
int t=0,cnt=0;
void tarjan(int cur,int pa){
    id[cur]=low[cur]=++t;
    on[cur]=true;
    st.p(cur);
    for(auto i:adj[cur]){
        if(!id[i.f]){
            tarjan(i.f,i.s);
            low[cur]=min(low[cur],low[i.f]);
        }
        else if(i.s!=pa)low[cur]=min(low[cur],low[i.f]);
    }
    if(low[cur]==id[cur]){
        cnt++;
        while(st.top()!=cur){
            g[st.top()]=cnt;
            on[st.top()]=false;
            st.pop();
        }
        on[st.top()]=false;
        g[st.top()]=cnt;
        st.pop();
    }
}
void dfs(int cur,int pa){
    on[cur]=true;
    for(auto i:adj2[cur]){
        if(i.f==pa)continue;
        if(on[i.f]){
            continue;
        }
        up[i.f][0]=cur;
        h[i.f]=h[cur]+1;
        dfs(i.f,cur);
    }
}
int lca(int a,int b){
    if(h[a]<h[b])swap(a,b);
    int k=h[a]-h[b];
    for(int i=0;i<=lg;i++)if(k&(1<<i))a=up[a][i];
    if(a==b)return a;
    for(int i=lg;i>=0;i--){
        if(up[a][i]!=up[b][i]){
            a=up[a][i];
            b=up[b][i];
        }
    }
    return up[a][0];
}
//ans 1=right,2 left
void push(int cur,int pa){
    if(on[cur])return;
    on[cur]=true;
    for(auto i:adj2[cur]){
        if(i.f==pa)continue;
        push(i.f,cur);
        if(info[i.f].f){
            if(info[i.f].f!=cur&&(!info[cur].f||h[info[i.f].f]<h[info[cur].f]))info[cur]=info[i.f];
            if(info[i.f].s){
                if(g[e[i.s].f]==i.f)ans[i.s]=1;
                else ans[i.s]=2;
            }
            else{
                if(g[e[i.s].f]==cur)ans[i.s]=1;
                else ans[i.s]=2;
            }
        }
    }
}
int32_t main(){
    fastio
    int n,m;cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        e.pb({u,v});
        adj[v].pb({u,i});
        adj[u].pb({v,i});
    }
    for(int i=1;i<=n;i++)if(!g[i])tarjan(i,-1);
    for(int i=1;i<=n;i++)for(auto j:adj[i])if(g[j.f]!=g[i])adj2[g[i]].pb({g[j.f],j.s});
    on.reset();
    for(int i=1;i<=cnt;i++)if(!on[i])dfs(i,-1);
    for(int j=1;j<=lg;j++)for(int i=1;i<=cnt;i++)up[i][j]=up[up[i][j-1]][j-1];
    int k;cin>>k;
    for(int i=0;i<k;i++){
        int u,v;cin>>u>>v;
        int a=u,b=v;
        u=g[u],v=g[v];
        if(u==v)continue;
        int node=lca(u,v);
        if(u!=node&&(info[u].f==0||h[info[u].f]>h[node]))info[u].f=node;
        if(v!=node&&(info[v].f==0||h[info[v].f]>h[node]))info[v].f=node;
        if(u!=node)info[u].s=1;
    }
    on.reset();
    for(int i=1;i<=cnt;i++)if(!on[i])push(i,-1);
    for(int i=0;i<m;i++){
        if(ans[i])cout<<((ans[i]==1)?"R":"L");
        else cout<<"B";
    }
}
