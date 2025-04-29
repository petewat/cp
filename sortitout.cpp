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
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-loops")
#define int long long
const int mod=998244353,mxn=2e5+5,lg=30,inf=1e18,minf=-1e9,Mxn=100000,root=700;
int n,k;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
pii merg(pii a,pii b){
	if(a.f==0&&b.f==0)return a;
	if(a.f>b.f)return a;
	else if(b.f>a.f)return b;
	else return {a.f,min(inf,a.s+b.s)};
}
struct seg{
	pii v[2*mxn+10];
	void update(int pos,pii val){
		pos+=n;
		v[pos]=merg(v[pos],val);
		for(int i=pos;i>0;i>>=1)v[i>>1]=merg(v[i],v[i^1]);
	}
	pii qry(int l,int r){
		pii ans={0,0};
		for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
			if(l&1)ans=merg(ans,v[l++]);
			if(!(r&1))ans=merg(ans,v[r--]);
		}
		return ans;
	}
}t;
int val[mxn+10];
pii dp[mxn+10];
bool yes[mxn+10];
bool cmp(pair<pii,pii> a,pair<pii,pii> b){
	if(a.f.f!=b.f.f)return a.f.f>b.f.f;
	return a.s.f>b.s.f;
}
bool del[mxn+10];
int32_t main(){
	setIO("itout");
	cin>>n>>k;
	for(int i=0;i<n;i++)cin>>val[i];
	for(int i=0;i<n;i++)dp[i]={0,1};
	vector<pair<pii,pii>>v;
	for(int i=n-1;i>=0;i--){
		dp[i]=merg(dp[i],t.qry(val[i],n));
		dp[i].f++;
		t.update(val[i],dp[i]);
		v.pb({dp[i],{val[i],i}});
		if(dp[i].s==0)assert(0);
	}
	vector<int>ans;
	sort(all(v),cmp);
	int last=-1,need=t.qry(0,n).f,lastval=0;
	cout<<n-need<<'\n';
	for(auto i:v){
		if(i.f.f==need&&i.s.s>last&&i.s.f>lastval){
			if(k>i.f.s)k-=i.f.s;
			else{
				last=i.s.s;
				lastval=i.s.f;
				need--;
				del[i.s.f]=true;
			}
		}
	}
	for(int i=1;i<=n;i++)if(!del[i])cout<<i<<'\n';
}