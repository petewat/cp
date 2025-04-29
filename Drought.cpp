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
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int v[mxn+10],ans=0,dp[202][2002],mx=0;
void add(int &x,int a){x=(x+a+mod)%mod;}
void solve(){
	dp[1][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=v[i];j++){
			if(v[i-1]-j>=0)add(dp[i][j],dp[i-1][v[i-1]-j]);
			add(dp[i][j],dp[i][j-1]);
		}
	}
	add(ans,dp[n][v[n]]);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=mx;j++)dp[i][j]=0;
		v[i]--;
	}
	/*
	dp(i,j) -> prefix [1,i-1] = 0 and val of prefix i = j
	transition:
	dp(i,j)->dp(i-1,k) where 0<=k<=val[i]-j
	dp(i,j)->dp(i+1,k-j) where -j<=k-j<=hi-j 
	0<=k-j<=hi-j
	*/
	
}
int32_t main(){
    fastio
	cin>>n;
	int mn=inf;
	for(int i=1;i<=n;i++)cin>>v[i],mn=min(mn,v[i]),mx=max(mx,v[i]);
	if(n%2==0)solve();
	else{
		for(int k=1;k<=mn+1;k++)solve();
	}
	cout<<ans;
}
/*
*/