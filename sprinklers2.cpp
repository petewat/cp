#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
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
#pragma GCC optimize ("03,unroll-loops")
using namespace std;
#define int long long
#define double long double
const int mod=1e9+7,mxn=5e3+5,lg=30,inf=1e18,minf=-1e18;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}	
int dp[2002][2002];
//last point at row i col j
char grid[2002][2002];
int ps[2002][2002],p[2002*2002];
int ps2[2002][2002];
int32_t main(){
	setIO("sprinklers2");
	int n;cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		cin>>grid[i][j];
		if(grid[i][j]!='W')ps[i][j]++;
	}
	p[0]=1;
	for(int i=1;i<=n*n;i++)p[i]=(p[i-1]*2)%mod;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ps[i][j]+=ps[i][j-1];
	int ans=0;
	for(int i=1;i<=n;i++){
		int sum=0;
		if(i==1)sum=1;
		for(int j=1;j<=n;j++){
			if(grid[i][j-1]!='W'){
				int mul=0;
				if(j-2>=0)mul=ps[i][j-2];
				dp[i][j]=(((sum*p[mul])%mod)*p[ps[i][n]-ps[i][j]])%mod;
				//new here so fix i,j-1
				//then mul by 2^n space before j-1
				//and
			}
			if(grid[i-1][j]!='W')sum=(sum+dp[i-1][j])%mod;
		}
		for(int j=1;j<=n;j++){
			int last=(dp[i-1][j]*p[ps[i][j-1]])%mod;//continue from last one
			if(grid[i-1][j]!='W')last=(last*2)%mod;//can now take that
			last=(last*p[ps[i][n]-ps[i][j]])%mod;
			dp[i][j]=(dp[i][j]+last)%mod;
		}
	}
	for(int i=n;i>=1;i--)for(int j=1;j<=n;j++)ps[i][j]+=ps[i+1][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(grid[i+1][n]!='W'&&grid[i][j]!='W')ans=(ans+(dp[i][j]*(p[max(0ll,ps[i+1][n]-1)]))%mod)%mod;
	if(grid[1][n]!='W')ans=(ans+p[(ps[1][n])-1])%mod;
	cout<<ans;
}