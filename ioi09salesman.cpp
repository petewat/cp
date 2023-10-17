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
const int mxn=5e5+10,mx=5e6+10,minf=-1e9;
int n,u,d,se;
vector<pii>day[mxn+110];
int v[mxn+10],g[mxn+10],v2[mxn+10];
struct seg{
	int s[2*mxn+110];
	void init(){for(int i=0;i<=2*mxn+100;i++)s[i]=minf;}
	void update(int pos,int val){
		pos+=mxn+5;
        s[pos]=max(val,s[pos]);
		for(;pos>0;pos>>=1)s[pos>>1]=max(s[pos],s[pos^1]);
	}
	int qry(int l,int r){
		int ans=minf;
		for(l+=mxn+5,r+=mxn+5;l<=r;l>>=1,r>>=1){
			if(l&1)ans=max(ans,s[l++]);
			if(!(r&1))ans=max(ans,s[r--]);
		}
		return ans;
	}
}t[2];
int32_t main(){
	cin>>n>>u>>d>>se;
	vector<ppii>q(n);
	for(int i=0;i<n;i++)cin>>q[i].f>>q[i].s.f>>q[i].s.s;
	t[0].init();
	t[1].init();
	t[0].update(se,d*se);
	t[1].update(se,-u*se);
	sort(all(q));
	for(auto i:q)day[i.f].pb(i.s);
	for(int i=0;i<=mxn+5;i++){
	  if(day[i].empty())continue;
		int mx2=minf,in=0;
		for(auto j:day[i]){
			g[in]=max(t[0].qry(0,j.f)-(d*j.f),t[1].qry(j.f,mxn+5)+(u*j.f))+j.s;
			v[in]=max(g[in],mx2+j.s-(d*j.f));
			mx2=max(mx2,v[in]+(d*j.f));
			in++;
		}
		in=day[i].size()-1;
		mx2=minf;
		reverse(all(day[i]));
		for(auto j:day[i])v2[in]=max(g[in],mx2+j.s+(u*j.f)),mx2=max(v2[in]-(u*j.f),mx2),in--;
        in=day[i].size()-1;
		for(auto j:day[i]){
			t[0].update(j.f,max(v[in],v2[in])+(d*j.f));
			t[1].update(j.f,max(v[in],v2[in])-(u*j.f));
			in--;
		}
	}
	cout<<max({t[0].qry(0,se)-(d*se),t[1].qry(se,mxn+1)+(u*se)});
}
/*
4 5 3 100
2 80 100
5 125 130
4 75 150
3 120 110
*/
