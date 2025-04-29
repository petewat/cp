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
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")
#define int long long
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
int cost[mxn+10],val[mxn+10],M;
int dp[mxn+10][3];
//0 1 2
//<= M, ==M, >=M
int get(int x,int y){
    if(y==0)return !(val[x]<=M);
    if(y==1)return !(val[x]==M);
    if(y==2)return !(val[x]>=M);
}
void caldp(int cur,int l,int r){
    for(int i=0;i<3;i++)dp[cur][i]=inf;
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=j;k<3;k++){
        vector<int>v={i,j,k};
        sort(all(v));
        dp[cur][v[1]]=min(dp[cur][v[1]],dp[l][j]+dp[r][k]+(cost[cur]*get(cur,i)));
        dp[cur][v[1]]=min(dp[cur][v[1]],dp[l][k]+dp[r][j]+(cost[cur]*get(cur,i)));
    }
}
int latest[mxn+10];
void dfs(int cur){
    if((cur<<1)+1<=n){
        dfs(cur<<1);
        dfs((cur<<1)+1);
        caldp(cur,cur<<1,(cur<<1)+1);
    }
    else{
        for(int i=0;i<3;i++)dp[cur][i]=(cost[cur]*get(cur,i));
    }
}
void update(int cur){
    while(cur){
        if((cur<<1)+1<=n)caldp(cur,cur<<1,(cur<<1)+1);
        else{
            for(int i=0;i<3;i++)dp[cur][i]=(cost[cur]*get(cur,i));
        }
        cur>>=1;
    }
}
int ans[mxn+10];
int32_t main(){
    fastio
	cin>>n;
    vector<pii>have;
    for(int i=1;i<=n;i++)cin>>val[i]>>cost[i],have.pb({val[i],i});
    int q;cin>>q;
    M=0;
    dfs(1);
    vector<pair<int,int>>qry(q);
    for(int i=0;i<q;i++)cin>>qry[i].f,qry[i].s=i;
    sort(all(qry));
    sort(all(have));
    int p1=0,p2=0;
    for(auto i:qry){
        M=i.f;
        while(p1<n&&have[p1].f<i.f)update(have[p1].s),p1++;
        while(p2<n&&have[p2].f<=i.f){
            if(have[p2].f==i.f)update(have[p2].s);
            p2++;
        }
        ans[i.s]=dp[1][1];
    }
    for(int i=0;i<q;i++)cout<<ans[i]<<'\n';
}
/*
*/