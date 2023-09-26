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
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
#define int long long
const int mxn=1e5,mod=1000000007,lg=25,root=1000,inf=1e18;
vector<int>adj[mxn+10];
int subsize[mxn+10],n;
int ansmn[mxn+10],ansmx[mxn+10],up[mxn+10][lg+10],h[mxn+10];
vector<int>sub[mxn+10];
int cnt=0;
int ans2=0,ans1=0;
bool cmp(int a,int b){return subsize[a]>subsize[b];}
void build(int cur,int p){
    subsize[cur]=1;
    for(auto i:adj[cur]){
        if(i==p)continue;
        build(i,cur);
        ans2+=min(subsize[i],n-subsize[i]);//we claim we can achive this
        subsize[cur]+=subsize[i];
    }
}
int getcentroid(int cur,int p){
    for(auto i:adj[cur]){
        if(i==p)continue;
        if(subsize[i]*2>n)return getcentroid(i,cur);
    }
    return cur;
}
void dfs(int cur,int p){
    sub[cnt].pb(cur);
    for(auto i:adj[cur]){
        if(i==p)continue;
        dfs(i,cur);
    }
}
int solvemn(int cur,int p){
    vector<int>v;
    for(auto i:adj[cur]){
        if(i==p)continue;
        if(solvemn(i,cur))v.pb(i);
    }
    if(v.size()){
        ans1++;
        ansmn[cur]=v[0];
        for(int i=0;i<v.size()-1;i++)ansmn[v[i]]=v[i+1],ans1+=2;
        ansmn[v.back()]=cur;
        ans1++;
    }
    else return 1;
    return 0;
}
void solvemx(){
    int node=getcentroid(1,-1);
    priority_queue<pii>pq;
    for(auto i:adj[node]){
        dfs(i,node);
        pq.push({sub[cnt].size(),cnt});
        cnt++;
    }
    int cur=node,tmp;
    ansmx[node]=sub[pq.top().s].back();
    cur=pq.top().s;
    pq.pop();
    while(!pq.empty()){
        ansmx[sub[cur].back()]=sub[pq.top().s].back();
        sub[cur].pop_back();
        tmp=cur;
        cur=pq.top().s;
        pq.pop();
        if(sub[tmp].size())pq.push({sub[tmp].size(),tmp});
    }
    ansmx[sub[cur].back()]=node;
}
int32_t main(){
    fastio
    cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    build(1,-1);
    solvemx();
    if(solvemn(1,-1)){
        int node=adj[1][0];
        ansmn[1]=node;
        int next=ansmn[node];
        while(ansmn[next]!=node)next=ansmn[next];
        ansmn[next]=1;
        ans1+=2;
    }
    cout<<ans1<<" "<<ans2*2<<'\n';
    for(int i=1;i<=n;i++)cout<<ansmn[i]<<" ";
    cout<<'\n';
    for(int i=1;i<=n;i++)cout<<ansmx[i]<<" ";
}
