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
using namespace std;
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
const int mod=1e9+7,mxn=2e5+5,lg=60,inf=1e18,minf=-1e18;
struct node{
	node *l,*r;
	int sz,p;
	char val;
	node(char a):val(a),sz(1),p(rand()),l(0),r(0){};
};
int get(node *cur){return (cur==NULL)?0:cur->sz;}
void merg(node *&cur,node *a,node *b){
	if(a==NULL)return void(cur=b);
	if(b==NULL)return void(cur=a);
	if(a->p<b->p){
		merg(a->r,a->r,b);
		cur=a;
	}
	else{
		merg(b->l,a,b->l);
		cur=b;
	}
	cur->sz=1+get(cur->l)+get(cur->r);
	return;
}
int cnt=0;
void split(node *cur,node *&a,node *&b,int val){
	if(cur==NULL)return void(a=b=NULL);
	if(get(cur->l)<val){//we can keep the whole left
		split(cur->r,cur->r,b,val-get(cur->l)-1);
		a=cur;
	}
	else{//go to left and the rest is right
		split(cur->l,a,cur->l,val);
		b=cur;
	}
	cur->sz=1+get(cur->l)+get(cur->r);
}
void print(node *cur){
	if(cur==NULL)return;
	print(cur->l);
	cout<<cur->val;
	print(cur->r);
}
int32_t main(){
	fastio
	srand(time(NULL));
	int n,q;cin>>n>>q;
	string a;cin>>a;
	node *root=new node(a[0]);
	for(int i=1;i<n;i++)merg(root,root,new node(a[i]));
	while(q--){
		int l,r;cin>>l>>r;
		node *a,*b;
		split(root,root,b,r);
		split(root,root,a,l-1);
		merg(root,root,b);
		merg(root,root,a);
	}
	print(root);
	return 0;
}
