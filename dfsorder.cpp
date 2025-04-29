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
const int mod=1e9+7,mxn=750+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int cost[mxn+10][mxn+10];
int dp[mxn+10][mxn+10];
int suf[mxn+10][mxn+10];
int32_t main(){
    fastio
	int n;cin>>n;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			int a;cin>>a;
			if(a>=0)cost[j][i]=a;
			else suf[j][i]=-a;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=n;j>=1;j--)suf[i][j]+=suf[i][j+1];
	}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)dp[i][j]=inf;
	for(int sz=2;sz<=n;sz++){
		for(int l=1,r=sz;r<=n;l++,r++){
			for(int k=l;k<r;k++){
				dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]+cost[l][k+1]+suf[k+1][r+1]);
			}
		}
	}
	cout<<dp[1][n];
}
/*
*/