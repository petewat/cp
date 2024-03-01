#include<bits/stdc++.h>
#pragma GCC optimize ("03,unroll-loops")
#include "manager.h"
using namespace std;
	/*
	manager{
		sub1->brute force nq (each q just loop and get greedy split)
		sub2 ->brute force (precompute for all x because x can only be <=10)
		sub3-> binary lift when x is known precompute binary lift table
		other sub is sqrt decom?
		if(x<sqrt) we can precompute the binary lifting
		else{
			we can binary search and and keep jumping
			because there can be at most k jump
			so we will binary search at most sqrt(n) times
			binary search cost lgn with lgn check->can we do any better
      use persist+bs to find the next
		}
	}
	*/
const int mxn=5e4,lg=16;
int root=310;
int jump[351][18][mxn+10],n;
unordered_map<int,int>mp;
struct node{
  node *l,*r;
  int val;
  node(): l(0),r(0),val(0){};
};
node*ps[mxn+10];
struct persist{
  void build(node*&cur,int l,int r){
    cur=new node();
    if(r==l)return;
    int mid=l+(r-l)/2;
    build(cur->l,l,mid);
    build(cur->r,mid+1,r);
  }
  void update(node *&cur,node *lcur,int l,int r,int pos,int val){
    cur=new node(*lcur);
    if(l==r){
      cur->val=val;
      return;
    } 
    int mid=l+(r-l)/2;
    if(pos<=mid)update(cur->l,lcur->l,l,mid,pos,val);
    else update(cur->r,lcur->r,mid+1,r,pos,val);
    cur->val=cur->l->val+cur->r->val;
  }
  int qry(int l,int r,node *cur,int x){
    int mid=l+(r-l)/2;
    if(l==r)return r;
    if(cur->l->val<=x)return qry(mid+1,r,cur->r,x-cur->l->val);
    else return qry(l,mid,cur->l,x);
  }
}t;
int getnx(int st,int x){
  return t.qry(1,n+1,ps[st],x);
}
void initialize(int N,int Q,vector<int>v){
	n=N;
  t.build(ps[n+1],1,n+1);
  for(int i=n;i>=1;i--){
    t.update(ps[i],ps[i+1],1,n+1,i,1);
    if(mp[v[i-1]])t.update(ps[i],ps[i],1,n+1,mp[v[i-1]],0);
    mp[v[i-1]]=i;
  }
  for(int r=1;r<=root;r++){
    for(int i=1;i<=n+1;i++)jump[r][0][i]=getnx(i,r);
    for(int j=1;j<=lg;j++){
      for(int i=1;i<=n+1;i++)jump[r][j][i]=jump[r][j-1][jump[r][j-1][i]];
    }
  }
}
int cur;
int lcur=-1;
int ans=0;
int min_managers(int l,int r,int x){
  ans=0;
  l++,r++;
  cur=l;
  if(x<=root){
    for(int i=lg;i>=0;i--)if(jump[x][i][cur]<=r){
      cur=jump[x][i][cur],ans+=(1<<i);
    }
    return ans+1;
  }
  else{
    lcur=-1;
    while(cur<=r){
      lcur=cur;
      cur=getnx(cur,x);
      if(cur==lcur)return 0;
      ans++;
    }
    return ans;
  }
}/*
int main()
{
  int N, Q;
  std::vector<int> A;

  std::cin >> N >> Q;
  for(int i=0; i<N; i++) {
    int a;
    std::cin >> a;
    A.push_back(a);
  }

  initialize(N, Q, A);

  for(int i=0; i<Q; i++) {
    int l, r, x;
    std::cin >> l >> r >> x;

    std::cout << min_managers(l, r , x) << std::endl;
  }
}
*/
