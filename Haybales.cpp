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
//#define endl "\n"
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
const int mod=1e9+7,mxn=2e5,inf=1e18,minf=-1e18,Mxn=2e6,lg=63;
int root;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}	
int n,k;
struct seg{
	int v[4*mxn+10],add[4*mxn+10];
	void init(){
		for(int i=0;i<=4*mxn;i++)v[i]=inf,add[i]=0;
	}
	void push(int l,int r,int pos){
		v[pos]+=add[pos];
		if(l!=r){
			add[pos*2]+=add[pos];
			add[pos*2+1]+=add[pos];
		}
		add[pos]=0;
	}
	void updatepoint(int l,int r,int pos,int qpos,int val){
		push(l,r,pos);
		if(l==r){
			v[pos]=val;
			return;
		}
		int mid=l+(r-l)/2;
		if(qpos<=mid)updatepoint(l,mid,pos*2,qpos,val);
		else updatepoint(mid+1,r,pos*2+1,qpos,val);
		v[pos]=min(v[pos*2],v[pos*2+1]);
	}
	void updaterange(int l,int r,int pos,int ql,int qr,int val){
		push(l,r,pos);
		if(r<l)return;
		if(l>qr||r<ql)return;
		if(l>=ql&&r<=qr){
			add[pos]+=val;
			push(l,r,pos);
			return;
		}
		int mid=l+(r-l)/2;
		updaterange(l,mid,pos*2,ql,qr,val);
		updaterange(mid+1,r,pos*2+1,ql,qr,val);
		v[pos]=min(v[pos*2],v[pos*2+1]);
	}
	int qry(int l,int r,int pos){
		push(l,r,pos);
		if(l==r)return r;
		int mid=l+(r-l)/2;
		push(l,mid,pos*2);
		push(mid+1,r,pos*2+1);
		if(v[pos*2]<=0)return qry(l,mid,pos*2);
		else return qry(mid+1,r,pos*2+1);
	}
	void print(int l,int r,int pos){
		push(l,r,pos);
		if(l==r){
			cout<<v[pos]<<" ";
			return;
		}
		int mid=l+(r-l)/2;
		print(l,mid,pos*2);
		print(mid+1,r,pos*2+1);
	}
}t;
struct fen{
	int fwk[mxn+10];
	void update(int pos,int val){for(int i=pos+1;i<=n+2;i+=(i&-i))fwk[i]+=val;}
	int qry(int pos){
		if(pos<0)return 0;
		int sum=0;
		for(int i=pos+1;i>0;i-=(i&-i))sum+=fwk[i];
		return sum;
	}
}t2;
bool cmp(pii a,pii b){return a.s<b.s;}
int32_t main(){
	fastio
	t.init();
	cin>>n>>k;
	vector<pii>v(n);
	vector<int>r(n),l(n),cnt(n,0),pos(n);
	for(int i=0;i<n;i++)cin>>v[i].f,v[i].s=i;
	sort(all(v));
	for(int i=0;i<n;i++)pos[v[i].s]=i;
	int cur=n-1;
	for(int i=n-1;i>=0;i--){
		while(cur>0&&v[cur].f>v[i].f+k)cur--;
		r[i]=cur+1;
	}
	cur=0;
	for(int i=0;i<n;i++){
		while(cur<n&&v[cur].f+k<v[i].f)cur++;
		l[i]=cur-1;
	}
	sort(all(v),cmp);
	t.updatepoint(0,n,1,n,inf);
	for(int i=0;i<n;i++){
		//cout<<pos[i]<<" "<<v[pos[i]].f<<' '<<l[pos[i]]<<' '<<t2.qry(l[pos[i]])<<'\n';
		cnt[i]=t2.qry(l[pos[i]])+t2.qry(n)-t2.qry(r[pos[i]]-1);
		t.updatepoint(0,n,1,pos[i],cnt[i]);
		t2.update(pos[i],1);
	}
	sort(all(v));
	for(int i=0;i<n;i++){
		int id=t.qry(0,n,1);
		t.updatepoint(0,n,1,id,inf);
		cout<<v[id].f<<'\n';
		t.updaterange(0,n,1,r[id],n,-1);
		t.updaterange(0,n,1,0,l[id],-1);
	}
	
}
/*
n
given sequnce
we can get the first character by getting the lowest number that can move upfront
if there are multiple with same value we can greedy take the closest one
now when move the ith value everything after i doesnt have to consider the ith that is moved

keep sufix max,min
1 2 3 4 5 6 G
we can binary search to find a position where the abs(g-mx)<=k&&abs(g-mn)<=k
lets call the position x
now the range from x to cur we can place in any of them
we want to find position y that is minimum and the value current value in y is > G

problems{
	how to keep a suffix structure to let use query
    treap
}
can also greedy take the first without blockeds
*/