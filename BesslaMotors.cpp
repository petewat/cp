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
const int mod=1e9+7,mxn=1e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q,C,R;
void setIO(string name){	
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
vector<pii>adj[mxn+10];
map<int,int>dist[mxn+10];
int32_t main(){
    fastio
    cin>>n>>m>>C>>R>>k;
    for(int i=0;i<m;i++){
        int a,b,c;cin>>a>>b>>c;
        adj[a].pb({b,c});
        adj[b].pb({a,c});
    }
    priority_queue<pair<int,pii>,vector<pair<int,pii>>,greater<pair<int,pii>>>pq;
    for(int i=1;i<=C;i++){
        pq.push({0,{i,i}});
    }
    while(!pq.empty()){
        int cur=pq.top().s.f,d=pq.top().f,F=pq.top().s.s;
        pq.pop();
        if(dist[cur].size()>=k)continue;
        if(dist[cur].find(F)!=dist[cur].end()&&dist[cur][F]!=d)continue;
        dist[cur][F]=d;
        for(auto i:adj[cur])if(d+i.s<=R){
            if(dist[i.f].size()>=k)continue;
            pq.push({d+i.s,{i.f,F}});
        }
    }
    int cnt=0;
    for(int i=C+1;i<=n;i++)if(dist[i].size()==k)cnt++;
    cout<<cnt<<'\n';
    for(int i=C+1;i<=n;i++)if(dist[i].size()==k)cout<<i<<'\n';
}