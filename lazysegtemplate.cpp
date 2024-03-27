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
const int mod=1e9+7,mxn=1e4+5,lg=30,inf=1e18,minf=-1e18;
int n;
struct seg{
	int v[4*mxn+10],add[mxn+10];
	void init(int n){for(int i=0;i<=4*n;i++)v[i]=add[i]=inf;}
	void push(int l,int r,int pos){
		v[pos]=min(v[pos],add[pos]);
		if(l!=r){
			add[pos*2]=min(add[pos],add[pos*2]);
			add[pos*2+1]=min(add[pos],add[pos*2+1]);
		}
		add[pos]=inf;
	}
	void update(int l,int r,int ql,int qr,int pos,int val){
		if(qr<ql)return;
		push(l,r,pos);
		if(l>qr||r<ql)return;
		if(ql<=l&&r<=qr){
			add[pos]=val;
			push(l,r,pos);
			return;
		}
		int mid=l+(r-l)/2;
		update(l,mid,ql,qr,pos*2,val);
		update(mid+1,r,ql,qr,pos*2+1,val);
		v[pos]=min(v[pos*2],v[pos*2+1]);
	}
	int qryr(int l,int r,int ql,int qr,int pos){
		if(qr<ql)return inf;
		push(l,r,pos);
		if(l>qr||r<ql)return inf;
		if(ql<=l&&r<=qr)return v[pos];
		int mid=l+(r-l)/2;
		return min(qryr(l,mid,ql,qr,pos*2),qryr(mid+1,r,ql,qr,pos*2+1));
	}
	int qry(int l,int r,int pos,int qpos){
		push(l,r,pos);
		if(l==r)return v[pos];
		int mid=l+(r-l)/2;
		if(qpos<=mid)return qry(l,mid,pos*2,qpos);
		return qry(mid+1,r,pos*2+1,qpos);
	}
	void updatepos(int l,int r,int pos,int qpos,int val){
		push(l,r,pos);
		if(l==r){
			add[pos]=val;
			push(l,r,pos);
			return;
		}
		int mid=l+(r-l)/2;
		if(qpos<=mid)updatepos(l,mid,pos*2,qpos,val);
		else updatepos(mid+1,r,pos*2+1,qpos,val);
		v[pos]=min(v[pos*2],v[pos*2+1]);
	}
	void updp(int pos,int val){updatepos(0,n,1,pos,val);}
	void updr(int l,int r,int val){update(0,n,l,r,1,val);}
	int q(int pos){return qry(0,n,1,pos);}
	int qr(int l,int r){return qryr(0,n,l,r,1);}
}t;
int32_t main(){
  
}
