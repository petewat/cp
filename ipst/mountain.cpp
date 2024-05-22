#include <vector>
#include "mountain.h"
#include<iostream>
#include<queue>
#include<cassert>
#include<algorithm>
#include<stack>
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define f first
#define s second
#define all(x) x.begin(),x.end()
using namespace std;
//cartesian tree?
#define int long long
const int mxn=1e5;
vector<int>adj[mxn+10];
int val[mxn+10],type[mxn+10];
int l[mxn+10],r[mxn+10],root=0,sz1[mxn+10],sz2[mxn+10],ans=0,n,tin[mxn+10],tout[mxn+10],rev[mxn+10];
//start end
int hvyp[mxn+10],up[mxn+10],sz[mxn+10],hvy[mxn+10],nothvy[mxn+10];
int var[mxn+10][2],cnt=0;
struct seg{
	int v[4*mxn+10],lazy[4*mxn+10],sum[4*mxn+10];
	void init(){for(int i=0;i<=4*n;i++)v[i]=lazy[i]=sum[i]=0;}
	void push(int l,int r,int pos){
		sum[pos]=(sum[pos]+(lazy[pos]*v[pos]));
		if(l!=r){
			lazy[pos*2]+=lazy[pos];
			lazy[pos*2+1]+=lazy[pos];
		}
		lazy[pos]=0;
	}
	void build(int l,int r,int pos){
		if(l==r){
			v[pos]=val[rev[l]];
			lazy[pos]=var[rev[l]][cnt];
			push(l,r,pos);
			return;
		}
		int mid=l+(r-l)/2;
		build(l,mid,pos*2);
		build(mid+1,r,pos*2+1);
		v[pos]=v[pos*2]+v[pos*2+1];
		sum[pos]=sum[pos*2]+sum[pos*2+1];
	}
	void update(int l,int r,int ql,int qr,int pos,int val){
		if(r<l)return;
		push(l,r,pos);
		if(l>qr||r<ql)return;
		if(l>=ql&&r<=qr){
			lazy[pos]+=val;
			push(l,r,pos);
			return;
		}
		int mid=l+(r-l)/2;
		update(l,mid,ql,qr,pos*2,val);
		update(mid+1,r,ql,qr,pos*2+1,val);
		v[pos]=v[pos*2]+v[pos*2+1];
		sum[pos]=sum[pos*2]+sum[pos*2+1];
	}
	int qry(int l,int r,int ql,int qr,int pos){
		if(r<l)return 0;
		push(l,r,pos);
		if(l>qr||r<ql)return 0;
		if(l>=ql&&r<=qr)return sum[pos];
		int mid=l+(r-l)/2;
		return qry(l,mid,ql,qr,pos*2)+qry(mid+1,r,ql,qr,pos*2+1);
	}
}t[2];
struct seg2{
	int v[2*mxn+10];
	void update(int pos,int val){
		pos+=n;
		v[pos]=val;
		for(int i=pos;i>0;i>>=1)v[i>>1]=v[i]+v[i^1];
	}
	int qry(int l,int r){
		int sum=0;
		for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
			if(l&1)sum+=v[l++];
			if(!(r&1))sum+=v[r--];
		}
		return sum;
	}
}t2[2];
int T=-1;
void hld(int cur,int p){
	if(cur==-1)return;
	tin[cur]=++T;
	hvy[cur]=-1;
	rev[tin[cur]]=cur;
	hvyp[cur]=p;
	nothvy[cur]=-1;
	if(l[cur]==-1)hvy[cur]=r[cur];
	else if(r[cur]==-1)hvy[cur]=l[cur];
	else hvy[cur]=((sz[l[cur]]>sz[r[cur]])?l[cur]:r[cur]);
	if(hvy[cur]!=-1)hld(hvy[cur],p),up[hvy[cur]]=cur;
	//keep b-d on not hvy path?
	if(l[cur]!=hvy[cur])hld(l[cur],l[cur]),up[l[cur]]=cur,nothvy[cur]=l[cur];
	if(r[cur]!=hvy[cur])hld(r[cur],r[cur]),up[r[cur]]=cur,nothvy[cur]=r[cur];
	tout[cur]=T;
}
void getsz(int cur){
	sz1[cur]=sz2[cur]=0;
	sz[cur]=1;
	if(l[cur]!=-1)getsz(l[cur]),sz1[cur]+=sz1[l[cur]],sz2[cur]+=sz2[l[cur]],sz[cur]+=sz[l[cur]];
	if(r[cur]!=-1)getsz(r[cur]),sz1[cur]+=sz1[r[cur]],sz2[cur]+=sz2[r[cur]],sz[cur]+=sz[r[cur]];
	if(type[cur]==1)sz1[cur]++;
	else if(type[cur]==2)sz2[cur]++;
}
void show(int id){
	cout<<'\n';
	for(int i=0;i<n;i++)cout<<t[id].qry(0,n-1,i,i,1)<<" ";
	cout<<'\n';
}
void add(int node,int x,int id){
	//add to ans
	bool yes=0;
	//one more case for the starting node
	ans+=(t[id].qry(0,n-1,tin[node],tin[node],1)*x);
	while(hvyp[node]!=root){
		ans+=(t[id].qry(0,n-1,tin[hvyp[node]],tin[up[node]],1))*x;
		int g=(t2[id].qry(tin[node],tout[node]));
		if(nothvy[node]!=-1)g-=t2[id].qry(tin[nothvy[node]],tout[nothvy[node]]);
		g=(g*val[node]*x);
		if(t[id^1].qry(0,n-1,tin[node],tin[node],1))ans+=g;
		node=up[hvyp[node]];
	}
	int g=(t2[id].qry(tin[node],tout[node]));
	if(nothvy[node]!=-1)g-=t2[id].qry(tin[nothvy[node]],tout[nothvy[node]]);
	g=(g*val[node]*x);
	if(t[id^1].qry(0,n-1,tin[node],tin[node],1))ans+=g;
	if(node!=root)ans+=((t[id].qry(0,n-1,tin[hvyp[node]],tin[up[node]],1))*x);
}
void change(int node,int x,int id){
	t[id].update(0,n-1,tin[node],tin[node],1,x);
	while(hvyp[node]!=root){
		node=up[hvyp[node]];
		t[id].update(0,n-1,tin[node],tin[node],1,x);
	}
}
void initialize(int32_t N,vector<int32_t> A,vector<int32_t>C){
	n=N;
	for(int i=0;i<n;i++)val[i]=A[i],type[i]=C[i];
	stack<int>st;
	for(int i=0;i<n;i++){
		if(val[i]>=val[root])root=i;
		l[i]=r[i]=-1;
		while(!st.empty()&&val[st.top()]<=val[i])l[i]=st.top(),st.pop();
		if(!st.empty())r[st.top()]=i;
		st.push(i);
	}
	getsz(root);
	up[root]=-1;
	hld(root,root);
	for(int i=0;i<n;i++){
		if(type[i]==1)t2[0].update(tin[i],1);
		if(type[i]==2)t2[1].update(tin[i],1);
		int a=sz1[i],b=sz2[i],c,d,e,f;
		if(l[i]==-1)c=0,d=0;
		else c=sz1[l[i]],d=sz2[l[i]];
		if(r[i]==-1)e=0,f=0;
		else e=sz1[r[i]],f=sz2[r[i]];
		ans+=((2*a*b)-(a*f)-(c*b)+(c*f)-(a*d)-(e*b)+(e*d))*val[i];
		var[i][0]=sz1[i];
		if(hvy[i]!=-1)var[i][0]-=sz1[hvy[i]];
		var[i][1]=sz2[i];
		if(hvy[i]!=-1)var[i][1]-=sz2[hvy[i]];
	}
	t[0].build(0,n-1,1);
	cnt=1;
	t[1].build(0,n-1,1);
	return;
}
long long race_cost(int32_t S, int32_t X){
	if(type[X]==S)return ans;
	if(type[X]==1)add(X,-1,1),change(X,-1,0),t2[0].update(tin[X],0);
	else if(type[X]==2)add(X,-1,0),change(X,-1,1),t2[1].update(tin[X],0);
	type[X]=S;
	if(type[X]==1)change(X,1,0),add(X,1,1),t2[0].update(tin[X],1);
	else if(type[X]==2)change(X,1,1),add(X,1,0),t2[1].update(tin[X],1);
	return ans;
	/*
5 2
3 4 5 1 6
0 0 0 1 2
2 1
1 4

1 0
0 1
0 0
2 1
1 4

5 1
3 4 5 1 6
0 0 0 1 2
1 4
*/
/*
**multiply by val***
equation for a node=2ab-af-cb+cf-ad-eb+ed
=(a-c)x(b-f)+(a-e)x(b-d)
can we store for only the hvy child
observation: if we increase{
	sz1[l] then the answer will go up by (sz2[i]-sz2[l[i]])*val;
}
we can keep sz[i]-sz[hvy[i]]
and do normal hld
but the case where node i is the starting of chanin
we can to compute it by itself

*/
	return ans;
}
