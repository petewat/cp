#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<cassert>
#include<unordered_map>
#include <queue>
#include <cstdint>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define s second
#define pii pair<int,int>
#define ppii pair<int,pii>
#define vi vector<int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-lopps")
#define int long long
#define double long double
using namespace std;
const int mod=998244353,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q,w;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
//dist to tini when node is centroid

int T=0;
void put(pair<pii,pii>&x,pii a){
    if(x.f.f<a.f){
        if(x.f.s!=a.s)x.s=x.f;
        x.f=a;
    }
    else if(x.s.f<a.f){
        if(x.f.s!=a.s)x.s=a;
    }
}
int sz[mxn+10],del[mxn+10];
int ans[mxn+10];
vector<pair<pii,int>>e;
vector<pii>adj[mxn+10];

int tin[mxn+10][lg+1],tout[mxn+10][lg+1],have[mxn+10][lg+1];

struct centroid_tree{
    int root,dept;
    vector<int>dist,deg;
    
    //{mx1,deg} {mx2,deg}
    vector<pair<pii,pii>>v;
    vector<int>lazy;
    int sz=0;
    void pull(int pos){
        v[pos]=v[pos<<1];
        put(v[pos],v[pos<<1|1].f);
        put(v[pos],v[pos<<1|1].s);
    }
    void build(int pos,int l,int r){
        v[pos]={{minf,-1},{minf,-1}};
        if(l==r)return void(put(v[pos],{dist[l],deg[l]}));
        int mid=l+(r-l)/2;
        build(pos<<1,l,mid);
        build(pos<<1|1,mid+1,r);
        pull(pos);
    }
    void apply(int pos,int x){
        v[pos].f.f+=x;
        if(v[pos].s.f!=minf)v[pos].s.f+=x;
        lazy[pos]+=x;
    }
    void push(int pos,int l,int r){
        if(l!=r){
            apply(pos<<1,lazy[pos]);
            apply(pos<<1|1,lazy[pos]);
        }
        lazy[pos]=0;
    }
    void update(int pos,int l,int r,int ql,int qr,int x){
        if(l>qr||r<ql)return;
        if(ql<=l&&r<=qr)return void(apply(pos,x));
        int mid=l+(r-l)/2;
        push(pos,l,r);
        update(pos<<1,l,mid,ql,qr,x);
        update(pos<<1|1,mid+1,r,ql,qr,x);
        pull(pos);
    }

    void getT(int cur,int p){
        tin[cur][dept]=++T;
        for(auto i:adj[cur])if(i.f!=p&&!del[i.f])getT(i.f,cur);
        tout[cur][dept]=T;   
    }
    void dfs(int cur,int p,int k){
        have[cur][dept]=root;
        deg[tin[cur][dept]]=k;
        for(auto i:adj[cur])if(i.f!=p&&!del[i.f]){
            dist[tin[i.f][dept]]=dist[tin[cur][dept]]+i.s;
            dfs(i.f,cur,k);
        }
    }
    void init(){
        T=0;
        getT(root,-1);
        int c=0;
        sz=T;
        deg.resize(sz+1);
        dist.resize(sz+1);
        have[root][dept]=root;
        for(int i=0;i<adj[root].size();i++)if(!del[adj[root][i].f]){
            dist[tin[adj[root][i].f][dept]]=adj[root][i].s;
            dfs(adj[root][i].f,root,c++);
        }
        sz=T;
        v.resize(4*(sz+2));
        lazy.resize(4*(sz+2));
        build(1,0,sz);
        ans[root]=v[1].f.f+max(0LL,v[1].s.f);
    }
}t[mxn+10];

void getsz(int cur,int p){sz[cur]=1;for(auto i:adj[cur])if(i.f!=p&&!del[i.f])getsz(i.f,cur),sz[cur]+=sz[i.f];}
int getcen(int cur,int p,int need){
    for(auto i:adj[cur])if(i.f!=p&&!del[i.f]){
        if(sz[i.f]>need)return getcen(i.f,cur,need);
    }
    return cur;
}
int ROOT=0;
void decomp(int cur,int p,int dept){
    getsz(cur,-1);
    int node=getcen(cur,-1,sz[cur]/2);
    if(dept==0)ROOT=node;
    t[node].root=node;
    t[node].dept=dept;
    t[node].init();
    del[node]=1;
    for(auto i:adj[node])if(!del[i.f])decomp(i.f,cur,dept+1);
}


int32_t main(){
    fastio
    cin>>n>>q>>w;
    for(int i=1;i<n;i++){
        int a,b,c;cin>>a>>b>>c;
        e.pb({{a,b},c});
        adj[a].pb({b,c});
        adj[b].pb({a,c});
    }
    decomp(1,-1,0);
    int last=0;
    priority_queue<pii>pq;
    for(int i=1;i<=n;i++)pq.push({ans[i],i});
    while(q--){
        int d,x;cin>>d>>x;
        d=(d+last)%(n-1);
        x=(x+last)%w;
        int delta=x-e[d].s;
        e[d].s=x;
        int cur=ROOT,cd=0;
        while(t[cur].sz>1){
            if(tin[e[d].f.f][cd]<tin[e[d].f.s][cd])swap(e[d].f.f,e[d].f.s);
            t[cur].update(1,0,t[cur].sz,tin[e[d].f.f][cd],tout[e[d].f.f][cd],delta);
            ans[cur]=t[cur].v[1].f.f+max(0LL,t[cur].v[1].s.f);
            pq.push({ans[cur],cur});
            if(e[d].f.f==cur||e[d].f.s==cur)break;
            cur=have[e[d].f.f][cd+1];
            cd++;
            if(cur==0)assert(0);
        }
        while(ans[pq.top().s]!=pq.top().f)pq.pop();
        last=pq.top().f;
        cout<<last<<'\n';
    }
}

/*

4 3 2000
1 2 100
2 3 1000
2 4 1000
2 1030
1 1020 
1 890

10 10 10000
1 9 1241
5 6 1630
10 5 1630
2 6 853
10 1 511
5 3 760
8 3 1076
4 10 1483
7 10 40
8 2051
5 6294
5 4168
7 1861
0 5244
6 5156
3 3001
8 5267
5 3102
8 3623
*/