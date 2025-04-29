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
//#include<bits/stdc++.h>
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
using namespace std;
#define int long long
#define double long double
const int inf=1e18;
int base=1e7;
double tmp=1e-7;
bool cmp(pair<double,int> a,pair<double,int> b){
	return b.f-a.f-tmp>0;
}
bool cmp2(double a,double b){
	return b-a-tmp>0;
}
int32_t main(){
	fastio
	int m,n;cin>>m>>n;
	double x=(m*2.0/n);
	vector<int>p;
	for(int i=0;i<n;i++){
		int a;cin>>a;
		p.pb(a);
		char b;cin>>b;
	}
	sort(all(p));
	vector<double>pos(n,0);
	for(int i=1;i<n;i++)pos[i]=pos[i-1]+x;
	vector<pair<double,int>>v;
	double l=0,r=m;
	auto get=[&](double mid){
		double x=0;
		vector<int>tmp;
		for(int i=0;i<n;i++)tmp.pb((v[i].f*1.0+(mid*1.0*v[i].s*1.0))*base);
		sort(all(tmp));
		for(int i=0;i<n;i++){
			double g=tmp[i]*1.0/base*1.0;
			x=max(x,abs(p[i]-g));
		}
		return x;
	};
	for(auto i:pos){
		if(i>=m-tmp){
			double g=(2*m);
			g-=i;
			v.pb({g,-1});
			r=min(r,g);
		}
		else v.pb({i,1}),r=min(r,m-i);
	}
	cout<<fixed<<setprecision(7);
	int mx=log2(r*base);
	sort(all(v),cmp);
	for(int i=0;i<=mx+2;i++){
		double mid=l+(r-l)/2*1.0;
		double t1=get(mid),t2=get(mid-tmp);
		if(t1>=t2)r=mid-tmp;
		else l=mid+tmp;
	}
	cout<<get(r);
}