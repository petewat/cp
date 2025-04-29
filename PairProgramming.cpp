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
#include <cstdint>
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
const int mod=1e9+7,mxn=3e5+5,lg=30,inf=1e18,minf=-1e18;
int n;
void mul(int &x,int a){x=(x*a)%mod;}
void add(int &x,int a){x=(x+a+mod)%mod;}
int dp[2002][2002],lasta[2002][2],lastb[2002][2];
string  get(string x){
	string ans="";
	int cur=0;
	for(int i=0;i<x.size();i++)if(x[i]=='0')cur=i+1,ans="0";
	for(int i=cur;i<x.size();i++){
		if(x[i]!='1')ans+=x[i];
	}
	return ans;
}
//0 is +
//1 is *
void solve(){
	cin>>n;
	string a,b;cin>>a>>b;
	a=get(a),b=get(b);
	int x=0,y=0;
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dp[i][j]=0;
	for(int i=0;i<=n;i++)for(int j=0;j<2;j++)lasta[i][j]=lastb[i][j]=-1;
	if(a.size()&&a[0]=='0'){
		x++;
		for(int i=0;i<b.size();i++)if(b[i]=='+')dp[1][i+1]=1;
	}
	if(b.size()&&b[0]=='0'){
		y++;
		for(int i=0;i<a.size();i++)if(a[i]=='+')dp[i+1][1]=1;
	}
	for(int i=a.size()-1;i>=0;i--){
		for(int j=0;j<2;j++)lasta[i][j]=lasta[i+1][j];
		if(a[i]=='+')lasta[i][0]=i;
		else lasta[i][1]=i;
	}
	for(int i=b.size()-1;i>=0;i--){
		for(int j=0;j<2;j++)lastb[i][j]=lastb[i+1][j];
		if(b[i]=='+')lastb[i][0]=i;
		else lastb[i][1]=i;
	}
	dp[x][y]++;
	for(int i=0;i<a.size();i++)for(int j=0;j<b.size();j++){
		if(a[i]=='+'&&b[j]=='+'){
			add(dp[i+1][j+1],dp[i][j]);
			if(lasta[i][1]!=-1)add(dp[lasta[i][1]+1][j],dp[i][j]);
			if(lastb[j][1]!=-1)add(dp[i][lastb[j][1]+1],dp[i][j]);
		}
		else if(a[i]!='+'&&b[j]!='+'){
			add(dp[i+1][j+1],dp[i][j]);
			if(lasta[i][0]!=-1)add(dp[lasta[i][0]+1][j],dp[i][j]);
			if(lastb[j][0]!=-1)add(dp[i][lastb[j][0]+1],dp[i][j]);
		}
		else{
			add(dp[i+1][j],dp[i][j]);
			add(dp[i][j+1],dp[i][j]);
		}
	}
	int ans=0;
	for(int i=0;i<=b.size();i++)add(ans,dp[a.size()][i]);
	for(int i=0;i<a.size();i++)add(ans,dp[i][b.size()]);
	cout<<ans<<'\n';
}
int32_t main(){
	fastio
	int t;cin>>t;
	while(t--)solve();
}
/*

*/
