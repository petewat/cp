#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second
#define pii pair<int,int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#define sz(x) (int)((x).size())
#define int long long
const int mod=998244353,mxn=3e5,inf=1e9,minf=-1e9,lg=30,Mxn=1e9;
//#undef int
int n,k,m,d,q;
vector<int>adj[mxn+10];
enum Type { Vertex, Compress, Rake, AddEdge, AddVertex };
struct sttree{
    int root=1,stroot;
    vector<int>P,L,R;
    vector<Type>T;
    int ct;
    sttree(){
        P.resize(4*n+1,-1),L.resize(4*n+1,-1),R.resize(4*n+1,-1);
        T.resize(4*n+1,Type::Vertex);
        ct=n;
        build();
    }
    private:
    int gethvy(int cur,int p){
        int sz=1,best=0;
        for(auto &i:adj[cur]){
            int x=gethvy(i,cur);
            sz+=x;
            if(x>best)best=x,swap(i,adj[cur][0]);
        }
        return sz;
    }
    int add(int k,int l,int r,Type t){
        if(k==-1)k=++ct;
        P[k]=-1,L[k]=l,R[k]=r,T[k]=t;
        if(l!=-1)P[l]=k;
        if(r!=-1)P[r]=k;
        return k;
    }
    pii merge(vector<pii>have, Type t){
        if(have.size()==1)return have[0];
        int cs=0;
        for(auto i:have)cs+=i.s;
        vector<pii>b,c;
        for(auto i:have){
            if(cs>i.s)b.pb(i);
            else c.pb(i);
            cs-=2*i.s;
        }
        pii x=merge(b,t),y=merge(c,t);
        return {add(-1,x.f,y.f,t),x.s+y.s};
    }
    pii compress(int cur){
        vector<pii>have={add_vertex(cur)};
        while(adj[cur].size())have.pb(add_vertex(cur=adj[cur][0]));
        return merge(have,Type::Compress);
    }
    pii rake(int cur){
        vector<pii>have;
        for(int i=1;i<adj[cur].size();i++)have.pb(add_edge(adj[cur][i]));
        return have.empty() ? (pii){-1, 0} : merge(have, Type::Rake);
    }
    pii add_edge(int cur){
        pii x=compress(cur);
        return {add(-1,x.f,-1,Type::AddEdge),x.s};
    }
    pii add_vertex(int cur){
        pii x=rake(cur);
        //type verte = end of chain
        return {add(cur,x.f,-1, x.f==-1 ? Type::Vertex : Type::AddVertex),x.s+1};
    }
    void build(){
        gethvy(root,-1);
        stroot=compress(root).f;
    }
};
int A[mxn+10];
struct path{int a,b;};
using point=int;
//end vertex
path vertex(int i){return {1,A[i]};}
//merging
path compress(path x,path y){return {(int)((1LL*x.a*y.a)%mod),(int)(((1LL*x.a*y.b)%mod+1LL*x.b)%mod)};}
point rake(point x,point y){return (int)((1LL*x*y)%mod);}
//convert from path <-> point
point addegde(path x){return x.b;}
path addvertex(point x,int i){return {x,A[i]};}
int32_t main(){
    fastio;
    cin>>n>>q;
    for(int i=2;i<=n;i++){
        int p;std::cin>>p;
        adj[p].pb(i);
    }
    for(int i=1;i<=n;i++)cin>>A[i];
    sttree stt;
    vector<path>Path(4*n+1);
    vector<point>Point(4*n+1);
    auto update=[&](int cur){
        if(stt.T[cur]==Type::Vertex){
            Path[cur]=vertex(cur);
        }
        else if(stt.T[cur]==Type::Compress){
            Path[cur]=compress(Path[stt.L[cur]],Path[stt.R[cur]]);
        }
        else if(stt.T[cur]==Type::Rake){
            Point[cur]=rake(Point[stt.L[cur]],Point[stt.R[cur]]);
        }
        else if(stt.T[cur]==Type::AddEdge){
            Point[cur]=addegde(Path[stt.L[cur]]);
        }
        else if(stt.T[cur]==Type::AddVertex){
            Path[cur]=addvertex(Point[stt.L[cur]],cur);
        }
    };
    function<void(int)>dfs=[&](int cur){
        if(stt.L[cur]!=-1)dfs(stt.L[cur]);
        if(stt.R[cur]!=-1)dfs(stt.R[cur]);
        update(cur);
    };
    dfs(stt.stroot);
    int cnt=0;
    while(q--){
        int v,x;cin>>v>>x;
        A[v]=x;
        while(v!=-1){
            update(v),v=stt.P[v];
        }
        std::cout<<Path[stt.stroot].b<<'\n';
    }
}