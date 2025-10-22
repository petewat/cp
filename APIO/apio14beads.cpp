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
const int mxn=2*1e5,mod=1000000007,lg=25,root=1000,inf=1e18;
int dp[mxn+10][2][2],up[mxn+10];
//state:cnt 1,2/found,not found root
vector<pii>adj[mxn+10];
void solve(int cur,int p){
    if(adj[cur].size()<=1&&p!=-1)return;
    vector<pii>v1,v2;
    int other=0,mx=0;
    for(auto i:adj[cur]){
        if(i.f==p)continue;
        up[i.f]=i.s;
        solve(i.f,cur);
        int mx1=max(dp[i.f][0][0],dp[i.f][1][0]);
        other+=mx1;
        mx=max(mx,max(dp[i.f][1][1],dp[i.f][0][1])-mx1);
        v1.pb({dp[i.f][1][0]-mx1+i.s,i.f});
        v2.pb({dp[i.f][1][1]-mx1+i.s,i.f});
    }
    sort(rall(v1));
    sort(rall(v2));
    dp[cur][0][0]=other+v1[0].f+up[cur];
    dp[cur][1][0]=other;
    if(p!=-1)dp[cur][0][1]=v2[0].f+other+up[cur];//cnt 1 
    else dp[cur][0][1]=other;
    dp[cur][1][1]=other+mx;//continue
    if(v1.size()>1)dp[cur][1][1]=max(dp[cur][1][1],other+v1[0].f+v1[1].f);//make
    if(v1[0].s!=v2[0].s)dp[cur][1][1]=max(dp[cur][1][1],other+v1[0].f+v2[0].f);
    else if(v1.size()>1)dp[cur][1][1]=max(dp[cur][1][1],other+max(v1[0].f+v2[1].f,v1[1].f+v2[0].f));
    //0 0
}
/*
0
1->max(2,1)+one (2)+i.s+up
2->max(2,1)
1
2->make->two 2 notfound+i.s
1->one 
*/
int32_t main(){
    fastio
    int n;cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v,w;cin>>u>>v>>w;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    solve(1,-1);
    cout<<max(dp[1][0][1],dp[1][1][1])<<'\n';
}
