#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<cassert>
#include<limits.h>
#include<cmath>
#include<set>
#include<numeric> //gcd(a,b)
#include<algorithm>
#include<bitset> 
#include<stack>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define pppiiii pair<pii,pii>
#define ppii pair<int,pii>
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-loops")
#define int long long
const int mod=1e9+7,mxn=2e5,lg=30,inf=1e18,minf=-1e18,Mxn=100000,root=700;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}	 
vector<int>adj[mxn+10];
int dp[mxn+10],mid;
bool canend[mxn+10];
bool can=true;
void dfs(int cur,int p){
	dp[cur]=0;
	canend[cur]=0;
	if(can==false)return;
	for(auto i:adj[cur])if(i!=p)dfs(i,cur);
	multiset<int>ms;
	for(auto i:adj[cur])if(i!=p)ms.insert(dp[i]+1);
	int val=-1,val2=-1;
	while(ms.size()>=1){
		int k=*(ms.begin());
		if(k>=mid){
			dp[cur]=k;
			return;
		}
		else val2=k;
		ms.erase(ms.begin());
		auto it=ms.lower_bound(mid-k);
		if(it==ms.end()){
			if(val!=-1)return void(can=false);
			val=k;
		}
		else{
			if((*it)>=mid)val2=k;
			if((*it)+k<mid)return void(can=false);
			ms.erase(it);
		}
	}
	if(val!=-1)dp[cur]=val;
	else{
		if(val2!=-1)dp[cur]=val2;
		canend[cur]=1;
	}
}
int32_t main(){
	setIO("deleg");
	fastio
	int n;cin>>n;
	for(int i=0;i<n-1;i++){
		int a,b;cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	int l=0,r=n-1,ans=minf;
	while(l<=r){
		mid=l+(r-l)/2;
		can=1;
		dfs(1,-1);
		int g=(canend[1]||dp[1]>=mid);
		can&=g;
		if(can)l=mid+1,ans=max(ans,mid);
		else r=mid-1;
	}
	if(ans==minf)assert(0);
	cout<<ans;
}