#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<float.h>
#include<limits.h>
#include <cassert>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric> //gcd(a,b)
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,ll>
#define ppii pair<int,pii>
#define vi vector<int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
using namespace std;
#define int long long
#define double long double
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-loops")
const int mod=1e9+7,mxn=3e5,lg=30,inf=1e18,minf=-1e9,Mxn=100000;
int n,m;
char grid[2002][2002];
int dp[2002][2002],val[2002],cost[2002][2002],on[2002];
bool vis[2002][2002];
int u[4]={0,0,1,-1},r[4]={1,-1,0,0};
int ans=0,sum=0;
int mn,mx;
void dfs(int cx,int cy){
    on[cy]=1;
    sum+=(grid[cx][cy]-'0');
    mn=min(mn,cy);
    mx=max(mx,cy);
    vis[cx][cy]=true;
    for(int i=0;i<4;i++){
        int nx=cx+u[i],ny=cy+r[i];
        if(nx<0||ny<0||nx>=n||ny>=m)continue;
        if(vis[nx][ny]||grid[nx][ny]=='.')continue;
        dfs(nx,ny);
    }
}
void solve(int l,int r,int opl,int opr,int k){
    if(l>r)return;
    int mid=l+(r-l)/2;
    int opt=mid;
    pii best={val[mid],mid};
    for(int j=min(opr,mid-1);j>=max(opl,0ll);j--)best=max(best,{dp[j][k-1]-cost[j][mid]+val[mid],j});
    dp[mid][k]=best.f;
    solve(l,mid-1,opl,best.s,k);
    solve(mid+1,r,best.s,opr,k);
}
int32_t main(){
    fastio
    int sub=0;
    cin>>n>>m;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>grid[i][j];
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        if(vis[i][j]||grid[i][j]=='.')continue;
        sum=0;
        mn=inf,mx=minf;
        dfs(i,j);
        for(int j=mn;j<=mx;j++)val[j]+=sum;
        cost[mn][mx]+=sum;
    }
    for(int i=0;i<m;i++)for(int j=0;j<m;j++)if(i)cost[i][j]+=cost[i-1][j];
    for(int i=0;i<m;i++)for(int j=m-1;j>=0;j--)cost[i][j]+=cost[i][j+1];
    for(int i=1;i<=m;i++)solve(0,m-1,0,m-1,i);
    for(int i=1;i<=m;i++){
        int ans=0;
        for(int j=0;j<m;j++)ans=max(ans,dp[j][i]);
        cout<<ans<<'\n';
    }
}
