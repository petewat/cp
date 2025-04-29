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
#include<stack>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define pppiiii pair<pii,pii>
#define ppii pair<int,pii>
#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-loops")
#define int long long
const int mod=998244353,mxn=2e5+5,lg=30,inf=1e18,minf=-1e9,Mxn=100000,root=700;
int n;
bool del[mxn+10];
vector<int>qry[mxn+10],adj[mxn+10];//time
int st[mxn+10],sz[mxn+10],h[mxn+10],ans[mxn+10],mx[mxn+10];
void getsz(int cur,int p){
    sz[cur]=1;
    for(auto i:adj[cur]){
        if(i==p||del[i])continue;
        getsz(i,cur);
        sz[cur]+=sz[i];
    }
}
int getcen(int cur,int p,int need){
    for(auto i:adj[cur])if(!del[i]&&i!=p&&sz[i]*2>need)return getcen(i,cur,need);
    return cur;
}
vector<pii>sub[mxn+10],allq[mxn+10];
void dfs(int cur,int p,int deg){
    mx[cur]=max(st[cur],mx[p]);
    sub[deg].pb({mx[cur],h[cur]});
    for(auto j:qry[cur])allq[deg].pb({cur,j});
    for(auto i:adj[cur])if(i!=p&&!del[i]){
        h[i]=h[cur]+1;
        dfs(i,cur,deg);
    }
}
struct seg{
    int v[2*mxn+10];
    void update(int pos,int val,int yes){
        pos+=n;
        if(yes)v[pos]=val;
        else v[pos]=max(v[pos],val);
        for(int i=pos;i>0;i>>=1)v[i>>1]=max(v[i],v[i^1]);
    }
    int qry(int l,int r){
        int ans=0;
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if(l&1)ans=max(ans,v[l++]);
            if(!(r&1))ans=max(ans,v[r--]);
        }
        return ans;
    }
}t;
void decom(int cur){
    getsz(cur,-1);
    int node=getcen(cur,-1,sz[cur]);
    h[node]=0;
    mx[node]=st[node];
    for(int i=0;i<adj[node].size();i++){
        if(del[adj[node][i]])continue;
        h[adj[node][i]]=1;
        dfs(adj[node][i],node,i);
    }
    for(int i=0;i<adj[node].size();i++){
        for(auto j:allq[i])if(j.s>=mx[j.f])ans[j.s]=max(ans[j.s],t.qry(0,j.s)+h[j.f]);
        for(auto j:sub[i])t.update(j.f,j.s,0);
    }
    for(int i=0;i<adj[node].size();i++)for(auto j:sub[i])t.update(j.f,0,1);
    for(int i=adj[node].size()-1;i>=0;i--){
        for(auto j:allq[i])if(j.s>=mx[j.f])ans[j.s]=max(ans[j.s],t.qry(0,j.s)+h[j.f]);
        for(auto j:sub[i])t.update(j.f,j.s,0);
    }
    for(auto i:qry[node])ans[i]=max(ans[i],t.qry(0,i));
    for(int i=0;i<adj[node].size();i++)for(auto j:sub[i])t.update(j.f,0,1);
    for(int i=0;i<adj[node].size();i++)sub[i].clear(),allq[i].clear();
    del[node]=true;
    for(auto i:adj[node])if(!del[i])decom(i);
}
void setIO(string name){        
    ios_base::sync_with_stdio(0); cin.tie(0);        
    freopen((name+".in").c_str(),"r",stdin);        
    freopen((name+".out").c_str(),"w",stdout);    
}
int32_t main(){
    setIO("newbarn");
    cin>>n;
    int cnt=1;
    fill(ans,ans+n+1,-1);
    for(int i=0;i<n;i++){
        char a;cin>>a;
        int x;cin>>x;
        if(a=='B'){
            if(x!=-1)adj[x].pb(cnt),adj[cnt].pb(x);
            st[cnt]=i;
            cnt++;
        }
        else qry[x].pb(i);
    }
    for(int i=1;i<cnt;i++)if(!del[i])decom(i);
    for(int i=0;i<n;i++)if(ans[i]!=-1)cout<<ans[i]<<'\n';
}