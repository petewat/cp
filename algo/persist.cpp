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
#define sz(x) (int)((x).size())
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
struct node{
    node *l,*r;
    int val;
    node():l(0),r(0),val(0){};
};
node *root[mxn+10];
struct persist{
    void build(node *&cur,int l=1,int r=n){
        cur=new node();
        if(l==r)return;
        int mid=l+(r-l)/2;
        build(cur->l,l,mid);
        build(cur->r,mid+1,r);
    }
    void update(node *&cur,node *last,int qpos,int val,int l=1,int r=n){
        cur=new node(*last);
        if(l==r)return void(cur->val=val);
        int mid=l+(r-l)/2;
        if(qpos<=mid)update(cur->l,last->l,qpos,val,l,mid);
        else update(cur->r,last->r,qpos,val,mid+1,r);
        cur->val=cur->l->val+cur->r->val;
    }
    int qry(node *cur,int ql,int qr,int l=1,int r=n){
        if(l>qr||r<ql)return 0;
        if(ql<=l&&r<=qr)return cur->val;
        int mid=l+(r-l)/2;
        return qry(cur->l,ql,qr,l,mid)+qry(cur->r,ql,qr,mid+1,r);
    }
}t;
int32_t main(){
	fastio
    int cnt=1;
    cin>>n>>q;
    t.build(root[1]);
    for(int i=1;i<=n;i++){
        int a;cin>>a;
        t.update(root[1],root[1],i,a);
    }
    while(q--){
        int x;cin>>x;
        if(x==1){
            int k,a,b;cin>>k>>a>>b;
            t.update(root[k],root[k],a,b);
        }
        else if(x==2){
            int k,a,b;cin>>k>>a>>b;
            cout<<t.qry(root[k],a,b)<<'\n';
        }
        else{
            int k;cin>>k;
            root[++cnt]=new node(*root[k]);
        }
    }
}
/*
5 0
1 1 2 3 2
1 5
2 4
3 5

*/