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
const int mxn=1e6,inf=1e9,minf=-1e9,mod=1e9+7;
int n;
bitset<(1LL<<20)>on[21];
vector<int>can[21];
void solve(){
	string a,b;cin>>a>>b;
	int x=0,y=0;
	for(int i=0;i<n;i++)if(a[i]=='1')x+=(1LL<<i);
	for(int i=0;i<n;i++)if(b[i]=='1')y+=(1LL<<i);
	int mask=0;
	if(!x)return void(cout<<0<<'\n');
	for(int ans=1;ans<=n;ans++){
		mask^=y;
		int mask2=0;
		for(int j=0;j<n;j++)if((mask&(1LL<<j))!=(x&(1LL<<j)))mask2^=(1LL<<j);
		if(on[ans][mask2])return void(cout<<ans<<'\n');
		y<<=1LL;
		y|=(!!(y&(1LL<<n)));
		y%=(1LL<<n);
	}
}
int X[22];
int32_t main(){
	fastio
	int t;cin>>t>>n;
	X[1]=1;
	for(int i=1;i<n;i++){
		X[i+1]=X[i]^(1LL<<i);
		if(i==1)for(int j=0;j<n;j++){
			on[i][(1LL<<j)]=1;
			can[i].pb(1LL<<j);
		}
		for(auto j:can[i]){
			for(int k=0;k<n;k++){
				int g=(j^(X[i+1]<<k));
				g%=(1LL<<n);
				if(k+i>=n)g^=X[k+i-n+1];
				if(!on[i+1][g])can[i+1].pb(g);
				on[i+1][g]=1;
			}
		}
		can[i].clear();
	}
	while(t--)solve();
}
/*
*/