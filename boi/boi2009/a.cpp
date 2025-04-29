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
#include <cstdlib> 
#include <cstdint>
using namespace std;
#define ll long long
#define f first
//#define endl "\n"
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
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define int long long
#define double long double
const int mod=1e9+7,mxn=1e7+5,lg=60,inf=1e18,minf=-1e18,Mxn=1e6+50000;
int dp[303][303][2];
int32_t main(){
	fastio
	int n,m;cin>>n>>m;
	vector<int>v(n);
	for(int i=0;i<n;i++)cin>>v[i];
	sort(all(v));
	auto get=[&](int a,int b){return abs(v[a]-v[b]);};
	int ans=0;
	for(int k=0;k<n;k++){
		for(int sz=0;sz<=k;sz++)for(int l=0,r=sz;r<n;l++,r++)for(int g=0;g<2;g++){
			if(sz)dp[l][r][g]=minf;
			else dp[l][r][g]=((m-abs(v[l]))*(k+1));
		}
		for(int sz=0;sz<=k;sz++){
			for(int l=0,r=sz;r<n;l++,r++){
				int affect=k-(r-l),x=l;
				if(sz==k){
					ans=max({ans,dp[l][r][0],dp[l][r][1]});
					continue;
				}
				if(l){
					dp[l-1][r][0]=max({dp[l-1][r][0],dp[l][r][0]-get(l,l-1)*affect,dp[l][r][1]-get(r,l-1)*affect});
					dp[l-1][r][1]=max(dp[l-1][r][1],dp[l-1][r][0]-(affect-1)*get(l-1,r));
				}
				if(r+1<n){
					dp[l][r+1][1]=max({dp[l][r+1][1],dp[l][r][0]-get(l,r+1)*affect,dp[l][r][1]-get(r,r+1)*affect});
					dp[l][r+1][0]=max(dp[l][r+1][0],dp[l][r+1][1]-((affect-1)*get(l,r+1)));
				}
			}
		}
	}
	cout<<ans;
	return 0;
}