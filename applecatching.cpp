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
bool cmp(pair<pii,int> a,pair<pii,int> b){
	if((a.f.f+a.f.s)==(b.f.f+b.f.s))return (a.f.s-a.f.f)<(b.f.s-b.f.f);
	return (a.f.f+a.f.s)<(b.f.f+b.f.s);
}
int32_t main(){
	fastio
	cin>>n;
	int ans=0;
	vector<pair<pii,int>>cow,apple;
	for(int i=0;i<n;i++){
		int q,t,x,ni;cin>>q>>t>>x>>ni;
		if(q==1)cow.pb({{x,t},ni});
		else apple.pb({{x,t},ni});
	}
	sort(all(cow),cmp);
	sort(all(apple),cmp);
	set<pii>have;
	int cur=apple.size()-1;
	for(int i=cow.size()-1;i>=0;i--){
		ans+=cow[i].s;
		while(cur>=0&&apple[cur].f.f+apple[cur].f.s>=cow[i].f.f+cow[i].f.s){
			have.insert({apple[cur].f.s-apple[cur].f.f,apple[cur].s});
			cur--;
		}
		auto it=have.lb({cow[i].f.s-cow[i].f.f,minf});
		int c=cow[i].s;
		while(c){
			if(it==have.end())break;
			if(c>=it->s){
				c-=it->s;
				it=have.erase(it);
			}
			else{
				pii x={it->f,it->s-c};
				have.erase(it);
				have.insert(x);
				c=0;
			}
		}
		ans-=c;
	}
	if(ans<0)assert(0);
	cout<<ans<<'\n';
}
/*
slope of -1 (left slope)
y+x=c
sort by x intercept which is c

for right slope
c=y-x
get y intercept=c
*/
