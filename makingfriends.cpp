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
const int mxn=2e5+5,inf=1e9,minf=-1e9;
int pa[mxn+10],n,m;
set<int>have[mxn+10];
int find(int u){return (pa[u]==u)?u:pa[u]=find(pa[u]);}
void merge(int a,int b){
	a=find(a),b=find(b);
	if(a==b)return;
	if(have[a].size()<have[b].size())swap(a,b);
	pa[b]=a;
	for(auto i:have[b])have[a].insert(i);
}
vector<int>adj[mxn+10];
int32_t main(){
	fastio
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(int i=1;i<=n;i++)pa[i]=i;
	int ans=0;
	for(int i=1;i<=n;i++){
		for(auto j:adj[i])if(j<i)merge(j,i);
		int x=find(i);
		while(have[x].size()&&(*have[x].begin())<=i)have[x].erase(have[x].begin());
		ans+=have[x].size();
		for(auto j:adj[i])if(j>i){
			if(have[x].find(j)!=have[x].end())ans--;
			else have[x].insert(j);
		}
	}
	cout<<ans;
}
/*
merge with node <current

*/