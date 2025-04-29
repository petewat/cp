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
const int mod=1e9+7,mxn=1e5+5,lg=30,inf=1e18,minf=-1e18,Mx=1e8;
int n;
int cal(int x){return (x*(x+1))/2;}
int get(int x,int y){
	int l=y,r=Mx,ans=inf;
	while(l<=r){
		int mid=l+(r-l)/2;
		if(cal(mid)-cal(y-1)>x)ans=min(ans,mid),r=mid-1;
		else l=mid+1;
	}
	return ans;
}
void solve(){
	cin>>n;
	vector<int>v(n);
	for(auto &i:v)cin>>i;
	sort(rall(v));
	int ans=min(v[0],cal(n));
	for(int i=1;i<v.size();i++){
		int k=get(v[i],i);
		if(k<=n)ans=min(ans,max(cal(k),v[i]));
	}
	if(ans==inf)assert(0);
	cout<<ans<<'\n';
}
int32_t main(){
	fastio
	int t;cin>>t;
	while(t--)solve();
}
/*

a b b a

a b a b
*/
