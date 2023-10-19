//http://codeforces.com/problemset/problem/484/E
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
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<ll,ll>
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
const int mxn=1e5,lg=25;
struct node{
    int mx,sf,pf,sum;
    node *l,*r;
    node(){
        mx=0,sf=0,pf=0,sum=0;
        l=NULL,r=NULL;
    }
};
struct qnode{
    int mx,sf,pf,sum;
    qnode(){
        mx=0,sf=0,pf=0,sum=0;
    }
};
bool cmp(pii a,pii b){return a.f<b.f;}
int in[mxn+10];
node *root[mxn+10];
node *comp(node *cl,node *cr,int mid,int l,int r){
    node *cur= new node();
    cur->l=cl;
    cur->r=cr;
    cur->mx=max(cr->mx,cl->mx);
    if(cl->sf&&cr->pf)cur->mx=max(cur->mx,cl->sf+cr->pf);
    cur->pf=cl->pf;
    cur->sf=cr->sf;
    if(cl->sum==mid-l+1)cur->pf=cl->sum+cr->pf;
    if(cr->sum==r-mid)cur->sf=cr->sum+cl->sf;
    cur->sum=cl->sum+cr->sum;
    return cur;
}
qnode comp2(qnode cl,qnode cr,int mid,int l,int r){
    qnode cur;
    cur.mx=cur.pf=cur.sf=cur.sum=0;
    cur.mx=max(cr.mx,cl.mx);
    if(cl.sf&&cr.pf)cur.mx=max(cur.mx,cl.sf+cr.pf);
    cur.pf=cl.pf;
    cur.sf=cr.sf;
    if(cl.sum==mid-l+1)cur.pf=cl.sum+cr.pf;
    if(cr.sum==r-mid)cur.sf=cr.sum+cl.sf;
    cur.sum=cl.sum+cr.sum;
    return cur;
}
void build(node *&cur,int l,int r){
    cur=new node();
    int mid=l+(r-l)/2;
    if(l==r)return;
    build(cur->l,l,mid);
    build(cur->r,mid+1,r);
}
void update(node *&cur,node *lcur,int l,int r,int pos){
    cur=new node(*lcur);
    if(l==r){
        cur->mx=cur->sf=cur->pf=cur->sum=1;
        return;
    }
    int mid=l+(r-l)/2;
    if(pos<=mid)update(cur->l,lcur->l,l,mid,pos);
    else update(cur->r,lcur->r,mid+1,r,pos);
    cur=comp(cur->l,cur->r,mid,l,r);
}

qnode tmp;
qnode qry(int l,int r,int ql,int qr,node *cur){
    int mid=l+(r-l)/2;
    tmp.mx=tmp.pf=tmp.sf=tmp.sum=0;
    if(ql>r||qr<l)return tmp;
    if(ql<=l&&qr>=r){
        tmp.mx=cur->mx;
        tmp.pf=cur->pf;
        tmp.sf=cur->sf;
        tmp.sum=cur->sum;
        return tmp;
    }
    return comp2(qry(l,mid,ql,qr,cur->l),qry(mid+1,r,ql,qr,cur->r),mid,l,r);
}
int32_t main(){
    fastio
    int n;cin>>n;
    vector<pii>v(n);
    for(int i=0;i<n;i++)cin>>v[i].f,v[i].s=i+1;
    sort(rall(v));
    build(root[0],0,mxn+5);
    int cnt=1;
    for(int i=0;i<v.size();i++){
        int c=i;
        bool yes=false;
        while(v[c].f==v[i].f&&c<n){
            if(!yes)update(root[cnt],root[cnt-1],0,mxn+5,v[c].s);
            else update(root[cnt],root[cnt],0,mxn+5,v[c].s);
            c++;
            yes=true;
        }
        in[cnt]=v[i].f;
        cnt++;
        i=c-1;
    }
    int m;cin>>m;
    int ql,qr,k,l,r,ans;
    while(m--){
        cin>>ql>>qr>>k;
        l=0,r=cnt-1,ans=INT_MAX;
        while(l<=r){   
            int mid=l+(r-l)/2;
            if(qry(0,mxn+5,ql,qr,root[mid]).mx>=k){
                ans=min(ans,mid);
                r=mid-1;
            }     
            else l=mid+1;
        }
        cout<<in[ans]<<'\n';
    }
}
