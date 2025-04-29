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
const int mod=1e9+7,mxn=1e4+5,lg=30,inf=1e18,minf=-1e18;
int n;
string a;
bitset<mxn+1>can[mxn+1],can2[mxn+1];
int dp[mxn+10];
int32_t main(){
	fastio
	cin>>n;
	cin>>a;
	for(int i=0;i<n;i++){
		if(a[i]=='R')can[i][i]=1;
		else if(a[i]=='B')can2[i][i]=1;
		else can[i][i]=can2[i][i]=1;
	}
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
		can[i][j]=(can[i][j-1]&can[j][j]);
		can2[i][j]=(can2[i][j-1]&can2[j][j]);
	}
	dp[0]=1;
	for(int i=0;i<=n;i++){
		if(i&&a[i-1]=='X')dp[i]=(dp[i-1]+dp[i])%mod;
		for(int sz=2;i+sz<=n;sz+=2){
			if(can[i][i+(sz/2)-1]&&can2[i+(sz/2)][i+sz-1]){
				dp[i+sz]=(dp[i+sz]+dp[i])%mod;
			}
		}
	}
	cout<<dp[n];
}