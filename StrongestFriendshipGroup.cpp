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
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
vector<int>adj[mxn+10];
int vis[mxn+10],tin[mxn+10],low[mxn+10];
int T=0,cnt=0;
int group[mxn+10],deg[mxn+10],dead[mxn+10];
stack<int>st;
int ans=0,c2=0;
void dfs(int cur,int p){
    if(vis[cur])return;
    tin[cur]=low[cur]=++T;
    vis[cur]=1;
    st.push(cur);
    c2++;
    for(auto i:adj[cur]){
        if(i==p)continue;
        if(!tin[i]){
            dfs(i,cur);
            low[cur]=min(low[cur],low[i]);
        }
        else low[cur]=min(low[cur],low[i]);
    }
    if(low[cur]==tin[cur]){
        int c=0;
        cnt++;
        vector<int>bro;
        while(st.top()!=cur)group[st.top()]=cnt,bro.pb(st.top()),st.pop();
        bro.pb(cur);
        group[cur]=cnt;
        st.pop();
        priority_queue<pii,vector<pii>,greater<pii>>pq;
        for(auto j:bro){
            c=0;
            for(auto k:adj[j])if(group[k]==group[j])c++;
            deg[j]=c;
            pq.push({deg[j],j});
        }
        int cursz=bro.size();
        int huh=0;
        while(!pq.empty()){
            int at=pq.top().s,cd=pq.top().f;
            pq.pop();
            if(deg[at]!=cd)continue;
            if(dead[at])continue;
            ans=max(ans,cursz*cd);
            for(auto k:adj[at])if(group[k]==group[at]){
                if(dead[k])continue;
                deg[k]--;
                deg[at]--;
                pq.push({deg[k],k});
            }
            dead[at]=1;
            cursz--;
        }
    }
}
vector<int>have[mxn+10];
int32_t main(){
    fastio
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    for(int i=1;i<=n;i++)if(!tin[i]){
        c2=0;
        dfs(i,-1);
        ans=max(ans,c2);
    }
    cout<<ans;
}
/*


*/