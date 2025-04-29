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
int n,k,m,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int u[4]={1,-1,0,0},r[4]={0,0,1,-1};
//D U R L
pii go[1010][1010];
int vis[1010][1010],cnt=0,CT;
pii where[mxn+10];
void dfs(int cx,int cy){
    if(!vis[cx][cy])cnt++;
    vis[cx][cy]=1;
    for(int i=0;i<4;i++){
        int nx=cx+u[i],ny=cy+r[i];
        if(nx>n+1||ny>n+1||ny<0||nx<0)continue;
        if(vis[nx][ny])continue;
        if(go[nx][ny].s>=CT||go[nx][ny].f==i)dfs(nx,ny);
    }
}
int32_t main(){
    fastio
    cin>>n>>q;
    for(int i=1;i<=q;i++){
        int x,y;cin>>x>>y;
        where[i]={x,y};
        char di;cin>>di;
        if(di=='U')go[x][y]={0,i};
        else if(di=='D')go[x][y]={1,i};
        else if(di=='L')go[x][y]={2,i};
        else go[x][y]={3,i};
    }
    cnt-=(4*n+4);
    vector<int>ans;
    for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)if(!go[i][j].s)go[i][j].s=inf;
    CT=q+1;
    dfs(0,0);
    ans.pb(cnt);
    for(int j=q;j>1;j--){
        CT--;
        int yes=0;
        for(int i=0;i<4;i++){
            int nx=where[j].f+u[i],ny=where[j].s+r[i];
            if(nx>n+1||ny>n+1||ny<0||nx<0)continue;
            yes|=vis[nx][ny];
        }
        if(yes)dfs(where[j].f,where[j].s);
        ans.pb(cnt);
    }
    if(cnt>(n*n))assert(0);
    reverse(all(ans));
    for(auto i:ans)cout<<(n*n)-i<<'\n';
}
/*
*/