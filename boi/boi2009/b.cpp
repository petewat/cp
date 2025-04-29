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
const int mod=1e9+7,mxn=1e5+5,lg=60,inf=1e18,minf=-1e18,Mxn=1e6+50000;
int get1(pii a){return a.f+a.s;}
int get2(pii a){return a.s-a.f;}//0 intercept
bool cmp(pair<pii,int> a,pair<pii,int> b){
	if(get1(a.f)!=get1(b.f))return get1(a.f)<get1(b.f);
	return get2(a.f)>get2(b.f);
}
//to cover (a cover b)
// get1(a)<get1(b) and get2(b)<get2(a);
int p[mxn+10];
int find(int u){return ((p[u]==u)?u:p[u]=find(p[u]));}
void merg(int a,int b){
	a=find(a),b=find(b);
	if(a==b)return;
	p[b]=a;
}
pii ans[mxn+10];
int id[mxn+10];
int32_t main(){
	fastio
	int n;cin>>n;
	vector<pair<pii,int>>v(n);
	for(int i=0;i<n;i++)cin>>v[i].f.s>>v[i].f.f,p[i+1]=i+1,v[i].s=i+1,ans[i+1]=v[i].f;
	sort(all(v),cmp);
	set<pii>st;
	for(auto i:v){
		auto it=st.lb({get2(i.f),0});
		if(it==st.end())st.insert({get2(i.f),i.s});
		else{
			merg((*it).s,i.s);
			st.erase(it);
			st.insert({get2(i.f),i.s});
		}
	}
	cout<<st.size()<<'\n';
	vector<int>com;
	for(int i=1;i<=n;i++)com.pb(find(i));
	sort(all(com));
	com.erase(unique(all(com)),com.end());
	for(int i=0;i<com.size();i++)id[com[i]]=i+1;
	for(int i=1;i<=n;i++){
		cout<<ans[i].s<<" "<<ans[i].f<<" "<<id[find(i)]<<"\n";
	}
	return 0;
}

/*
*/