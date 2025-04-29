#include<iostream>
#include <random>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<cassert>
#include<unordered_map>
#include <queue>
#include <cstdint>
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
#pragma GCC optimize ("03,unroll-lopps")
#define int long long
using namespace std;
const int mod=1e9+7,mxn=2e5,inf=1e9,minf=-1e9,lg=30;
//#undef int
int n,k,m,d,q,T;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);
}
mt19937 rng(time(NULL));
struct node{
    node *l,*r;
    int tag=0,p,sz;
    char val;
    node(char x):l(0),r(0),sz(1),tag(0),val(x),p(rng()){};
};
struct treap{   
    node *root;
  int get(node *x){return (x==NULL)?0:x->sz;}
    void pull(node *&cur){
        cur->sz=get(cur->l)+get(cur->r)+1;
    }
    void push(node *&cur){
        if(cur==NULL)return;
        if(cur->tag){
            swap(cur->l,cur->r);
            cur->tag=0;
            if(cur->l!=NULL)cur->l->tag^=1;
            if(cur->r!=NULL)cur->r->tag^=1;
        }
    }
    void split(node *&L,node *&R,node *cur,int x){
        if(cur==NULL)return void(L=R=NULL);
        push(cur);
        if(get(cur->l)<x){
            split(cur->r,R,cur->r,x-(get(cur->l))-1);
            L=cur;
        }
        else{
            split(L,cur->l,cur->l,x);
            R=cur;
        }
        pull(cur);
    }
    void merge(node *L,node *R,node *&cur){
        if(L==NULL)return void(cur=R);
        if(R==NULL)return void(cur=L);
        push(L);
        push(R);
        if(L->p<=R->p){
            merge(L->r,R,L->r);
            cur=L;
        }
        else{
            merge(L,R->l,R->l);
            cur=R;
        }
        pull(cur);
    }
    void print(node *cur){
        if(cur==NULL)return;
        push(cur);
        print(cur->l);
        cout<<cur->val;
        print(cur->r);
    }
}t;
int32_t main(){
    fastio
    cin>>n>>q;
    string a;cin>>a;
	node *root=new node(a[0]);
	for(int i=1;i<n;i++)t.merge(root,new node(a[i]),root);
	while(q--){
		int l,r;cin>>l>>r;
		node *t1,*t2;
		t.split(root,t2,root,r);
		t.split(root,t1,root,l-1);
		t1->tag^=1;
		t.merge(root,t1,root);
		t.merge(root,t2,root);
	}
	t.print(root);

}
/*
5 0
1 1 2 3 2
1 5
2 4
3 5

*/