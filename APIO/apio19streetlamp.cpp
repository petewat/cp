//offline2d bit  'o'
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
//#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-loops")
#define int long long
const int mod=1e9+7,mxn=3e5,lg=30,inf=1e18,minf=-1e18,Mxn=3725000,root=700;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}	 
int active=0;
int n,q,bruh=0;
struct fen2d{
/*
	l, add at l, stop at x+1
	r add at x,stop at r+1
	l,t x+1,-t
	x,t r+1,-t
	first{
		update(l,x,t)
		update(l,r+1,-t)
		update(x+1,x,-t)
		update(x+1,r+1,t)
	}*/
	vector<int>element[mxn+10];
	int e[Mxn+10],st[Mxn+10],fwk[Mxn+10];
	int cnt=0;
	void init(){
		int m=0;
		active=1;
		for(int i=0;i<n;i++){
			st[i]=m;
			sort(all(element[i]));
			element[i].erase(unique(all(element[i])),element[i].end());
			if(st[i]+element[i].size()>Mxn)return;
			copy(all(element[i]),e+st[i]);
			m+=element[i].size();
		}
		st[n]=m;
	}
	void update(int x,int y,int val){ 
		if(!active){
			for(;x<=n;x+=(x&-x)){
				bruh++;
				if(x==0)return;
				element[x-1].pb(y);
			}
			return;
		}
		for(;x<=n;x+=(x&-x)){
			if(x==0)return;
			int k=ub(e+st[x-1],e+st[x],y)-(e+st[x-1]);
		//	k=min(k,st[x]-st[x-1]);
			while(k<=st[x]-st[x-1]){
				if(k==0)return;
				if(st[x-1]+k-1<0)return;
				fwk[st[x-1]+k-1]+=val;
				k+=(k&-k);
			}
		}
	}
	int qry(int x,int y){
		int sum=0;
		for(;x>0;x-=(x&-x)){
			if(x==0)return sum;
			int k=ub(e+st[x-1],e+st[x],y)-(e+st[x-1]);
	//		k=min(k,st[x]-st[x-1]);
			while(k){
				if(k==0)return sum;
				if(st[x-1]+k-1<0)return 0;
				sum+=fwk[st[x-1]+k-1];
				k-=(k&-k);
			}
		}
		return sum;
	}
	void addrange(int l,int r,int x,int val){
		update(l,x,val);
		update(l,r+1,-val);
		update(x+1,x,-val);
		update(x+1,r+1,val);
	}
}t;
struct seg{
	int v[2*mxn+10];
	void update(int pos,int val){
		pos+=n+1;
		v[pos]=val;
		for(int i=pos;i>0;i>>=1)v[i>>1]=(v[i]&v[i^1]);
	}
	int qry(int l,int r){
		int ans=1;
		for(l+=n+1,r+=n+1;l<=r;l>>=1,r>>=1){
			if(l&1)ans=(ans&v[l++]);
			if(!(r&1))ans=(ans&v[r--]);
		}
		return ans;
	}
}t2;
int getl(int x){
	int l=1,r=x;
	int ans=x;
	while(l<=r){
		int mid=l+(r-l)/2;
		if(t2.qry(mid,x))r=mid-1,ans=min(ans,mid);
		else l=mid+1;
	}
	return ans;
}
int getr(int x){
	int l=x,r=n;
	int ans=x;
	while(l<=r){
		int mid=l+(r-l)/2;
		if(t2.qry(x,mid))l=mid+1,ans=max(ans,mid);
		else r=mid-1;
	}
	return ans;
}
int32_t main(){
	fastio
	cin>>n>>q;
	string a;cin>>a;
	a='b'+a;
	string keep=a;
	for(int i=1;i<=n;i++)if(a[i]=='1')t2.update(i,1);
	vector<pair<pii,pii>>qry;
	for(int i=0;i<q;i++){
		string ty;cin>>ty;
		if(ty=="query"){
			int l,r;cin>>l>>r;
			r--;
			qry.pb({{1,0},{l,r}});
		}
		else{
			int x;cin>>x;
			if(x>n)return 0;
			if(a[x]=='1'){
				int gl=getl(x),gr=getr(x);
				if(gl<=0||gr>n)return 0;
				t.addrange(gl,gr,x,0);
				qry.pb({{2,x},{gl,gr}});
				a[x]='0';
				t2.update(x,0);
			}
			else{
				a[x]='1';
				t2.update(x,1);
				int gl=getl(x),gr=getr(x);
				if(gl<=0||gr>n)return 0;
				t.addrange(gl,gr,x,0);
				qry.pb({{2,x},{gl,gr}});
			}
		}
	}
	for(int i=1;i<=n;i++)t2.update(i,(keep[i]=='1'));
	t.init();
	a=keep;
	for(int i=0;i<q;i++){
		if(qry[i].f.f==1){
			int ans=t.qry(qry[i].s.f,qry[i].s.s);
			if(t2.qry(qry[i].s.f,qry[i].s.s))ans+=(i+1);
			cout<<ans<<'\n';
		}
		else{
			int x=qry[i].f.s;
			if(a[x]=='1'){
				t.addrange(qry[i].s.f,qry[i].s.s,x,i+1);
				a[x]='0';
				t2.update(x,0);
			}
			else{
				a[x]='1';
				t2.update(x,1);
				t.addrange(qry[i].s.f,qry[i].s.s,x,-i-1);
			}
		}
	}
	/*

	qry l->r

	turn on at x ->lf,ri of continuos segment then every lf<=l<=x,x<=r<=ri will start -> -t
	turn of at x->lf,ri of contiuos segment then every lf<=l<=x,x<=r<=ri will end -> +t
	qry l,r->if l,r still on then ans=l,r+t->to end else ans=l,r

	update can be done by 2d offline fenwick
	finding lf and ri can be dones by binary search and seg tree?

	*/
}
