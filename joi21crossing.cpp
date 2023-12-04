//nice hashing + segtree problem
//hash[i]=(hash[i-1]+(base^i)*ascii)%mod
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
#include <iomanip>
#include<numeric>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
//#define s second
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
const int mod=1e9+7,mxn=2e5+5,lg=30,inf=1e18,minf=-1e18,base=101;
int p[mxn+10],n;
char g[4]={'l','J','O','I'};
int hashchar(char a){
	if(a=='J')return 1;
	else if(a=='O')return 2;
	return 3;
}
int getpow(int l,int r){return l==0?p[r]:(p[r]-p[l-1]+mod)%mod;}
int hashstring(string a){
	int ans=0;
	for(int i=0;i<a.size();i++)ans=(ans+(getpow(i,i)*hashchar(a[i])))%mod;
	return ans;
}
string comb(string a,string b){
	string ans="";
	for(int i=0;i<n;i++){
		if(a[i]==b[i])ans+=a[i];
		else ans+=g[6-(hashchar(a[i])+hashchar(b[i]))];
	}
	return ans;
}
string in;
struct seg{
	int v[4*mxn+10],add[4*mxn+10];
	void push(int l,int r,int node){
		if(add[node]==0)return;
		v[node]=(getpow(l,r)*add[node])%mod;
		if(l!=r)add[node<<1]=add[(node<<1)^1]=add[node];
		add[node]=0;
	}
	void build(int l,int r,int node){
		if(l==r){
			v[node]=(hashchar(in[l])*getpow(l,l))%mod;
			return;
		}
		int mid=l+(r-l)/2;
		build(l,mid,node<<1);
		build(mid+1,r,(node<<1)^1);
		v[node]=(v[node<<1]+v[(node<<1)^1])%mod;
	}
	void update(int l,int r,int ql,int qr,int node,int val){
		push(l,r,node);
		if(l>qr||r<ql)return;
		if(l>=ql&&r<=qr){
			add[node]=val;
			push(l,r,node);
			return;
		}
		int mid=l+(r-l)/2;
		update(l,mid,ql,qr,node<<1,val);
		update(mid+1,r,ql,qr,(node<<1)^1,val);
		v[node]=(v[node<<1]+v[(node<<1)^1])%mod;
	}
}t;
map<int,bool>mp;
int32_t main(){
	fastio
	cin>>n;
	p[0]=1;
	for(int i=1;i<=n;i++)p[i]=(((p[i-1]*base)%mod)+p[i-1])%mod;
	string s[3];
	for(int i=0;i<3;i++)cin>>s[i];
	for(int i=0;i<3;i++){
		mp[hashstring(s[i])]=true;
		for(int j=0;j<3;j++){
			if(i==j)continue;
			if(i<j){
				string tmp=(comb(s[i],s[j]));
				mp[hashstring(tmp)]=true;
				tmp=comb(s[3-(i+j)],tmp);
				mp[hashstring(tmp)]=true;
			}
		}
	}
	int q;cin>>q;
	cin>>in;
	t.build(0,n-1,1);
	if(mp[t.v[1]])cout<<"Yes\n";
	else cout<<"No\n";
	while(q--){
		int l,r;
		cin>>l>>r;
		char L;cin>>L;
		l--,r--;
		t.update(0,n-1,l,r,1,hashchar(L));
		if(mp[t.v[1]])cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
