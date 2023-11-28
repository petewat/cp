//sack practice

#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
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
//#define p push
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-lopps")
using namespace std;
const int mod=9901,mxn=4e5+5;
int tin[mxn+10],tout[mxn+10],l[mxn+10],r[mxn+10],pos[mxn+10],fwk[mxn+10];
ll sz[mxn+10],dp[mxn+10];
int cnt=0,n,node,t=0,sum;
void upd(int p,int val){for(int i=p;i<=n;i+=(i&-i))fwk[i]+=val;}
int qry(int p){
	sum=0;
	for(int i=p;i>0;i-=(i&-i))sum+=fwk[i];
	return sum;
}
int input(){
	int cur;cin>>cur;
	if(cur==0){
		cur=++cnt;
		l[cur]=input();
		r[cur]=input();
		tin[cur]=tin[l[cur]];
		tout[cur]=tout[r[cur]];
		sz[cur]=sz[l[cur]]+sz[r[cur]];
	}
	else{
		tin[cur]=tout[cur]=++t;
		pos[t]=cur;
		sz[cur]++;
	}
	return cur;
}
void solve(int cur,int keep){
	if(cur<=n){
		if(keep)upd(pos[tin[cur]],1);
		return;
	}
	if(sz[l[cur]]<sz[r[cur]])swap(l[cur],r[cur]);//left keep
	solve(r[cur],0);
	solve(l[cur],1);
	ll invcnt=0;
	for(int i=tin[r[cur]];i<=tout[r[cur]];i++)invcnt+=qry(pos[i]);
	dp[cur]=dp[l[cur]]+dp[r[cur]]+min(invcnt,(sz[l[cur]]*sz[r[cur]])-invcnt);
	if(keep)for(int i=tin[r[cur]];i<=tout[r[cur]];i++)upd(pos[i],1);
	else for(int i=tin[l[cur]];i<=tout[l[cur]];i++)upd(pos[i],-1);
}
int32_t main(){
    fastio
	cin>>n;
	cnt=n;
	input();
	solve(n+1,1);
	cout<<dp[n+1];
}
