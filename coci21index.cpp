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
//#include "combo.h"
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define ppii pair<pii,pii>
#define vi vector<int>
#define pb push_back
//#define p push
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
#define int long long
const int mod=1e9+7,mxn=2*1e5,inf=mxn+5,lg=25;
int n,m;
bitset<mxn+10>yes;
struct node{
    node *l,*r;
    int val;
    node():val(0),l(0),r(0){}
};
node* root[mxn+10];
vector<int>g[mxn+10];
void build(node*&a,int l,int r){
    a=new node();
    int mid=l+(r-l)/2;
    if(l==r)return;
    build(a->l,l,mid);
    build(a->r,mid+1,r);
}
void update(node *&ncur,node *lcur,int val,int pos,int l,int r){
    ncur=new node(*lcur);
    if(l==r){
        ncur->val+=val;
        return;
    }
    int mid=l+(r-l)/2;
    if(pos<=mid) update(ncur->l,lcur->l,val,pos,l,mid);
    else update(ncur->r,lcur->r,val,pos,mid+1,r);
    ncur->val=ncur->l->val+ncur->r->val;
}
int qry(int l,int r,int ql,int qr,node *cur){
    if(ql>r||qr<l)return 0;
    if(ql<=l&&r<=qr)return cur->val;
    int mid=l+(r-l)/2;
    return qry(l,mid,ql,qr,cur->l)+qry(mid+1,r,ql,qr,cur->r);
}
int32_t main(){
    fastio
    cin>>n>>m;
    int mx=0;
    vector<pii>v;
    for(int i=1;i<=n;i++){
        int a;cin>>a;
        v.pb({a,i});
        g[a].pb(i);
        mx=max(mx,a);
    }
    build(root[mx+1],1,n);
    v.pb({mx+1,0});
    for(int i=mx;i>=1;i--){
        bool again=true;
        if(g[i].size()==0)update(root[i],root[i+1],0,1,1,n);
        else for(auto j:g[i]){
            if(again)update(root[i],root[i+1],1,j,1,n);
            else update(root[i],root[i],1,j,1,n);
            again=false;
        }
    }
    for(int i=0;i<m;i++){
        int ql,qr;cin>>ql>>qr;
        int ans=0;
        int l=0,r=mx;
        while(l<=r){
            int mid=l+(r-l)/2;
            int cnt=qry(1,n,ql,qr,root[mid]);
            if(cnt>=mid){
                l=mid+1;
                ans=max(ans,mid);
            }
            else r=mid-1;
        }
        cout<<ans<<'\n';
    }
}
