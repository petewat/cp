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
const int mod=9901,mxn=4*1e5+5,inf=1e18,lg=25,minf=-1e18;
int seg[4*mxn+10],add[4*mxn+10],nxt[mxn+10],up[mxn+10][lg+5];
pii pos[mxn+10];
vector<int>v;
vector<pii>id;
void init(){for(int i=0;i<=4*mxn+5;i++)seg[i]=inf,add[i]=inf;}
void push(int pos,int l,int r){
    seg[pos]=min(seg[pos],add[pos]);
    if(l!=r){
        add[pos*2]=min(add[pos],add[pos*2+1]);
        add[pos*2+1]=min(add[pos],add[pos*2+1]);
    }
    add[pos]=inf;
}
int qry(int l,int r,int ql,int qr,int pos){
    push(pos,l,r);
    int mid=l+(r-l)/2;
    if(l>qr||r<ql)return inf; 
    if(ql<=l&&r<=qr)return seg[pos];
    return min(qry(l,mid,ql,qr,pos*2),qry(mid+1,r,ql,qr,pos*2+1));
}
void update(int l,int r,int ql,int qr,int pos,int val){
    push(pos,l,r);
    int mid=l+(r-l)/2;
    if(l>qr||r<ql)return;
    if(ql<=l&&r<=qr){
        add[pos]=min(add[pos],val);
        push(pos,l,r);
        return;
    }
    update(l,mid,ql,qr,pos*2,val);
    update(mid+1,r,ql,qr,pos*2+1,val);
    seg[pos]=min(seg[pos*2],seg[pos*2+1]);
}
int32_t main(){
    fastio
    int n;cin>>n;
    for(int i=0;i<n;i++){
        int a,b;cin>>a>>b;
        id.pb({a,b});
        v.pb(a);
        v.pb(b);
    }
    sort(all(v));
    for(int i=0;i<n;i++){
        pos[i].f=lb(all(v),id[i].f)-v.begin();
        pos[i].s=lb(all(v),id[i].s)-v.begin();
    }
    init();
    nxt[n]=n;
    for(int i=n-1;i>=0;i--){
        nxt[i]=qry(0,mxn+5,pos[i].f,pos[i].s,1);
        update(0,mxn+5,pos[i].f,pos[i].s,1,i);
        nxt[i]=min(nxt[i],nxt[i+1]);
        up[i][0]=nxt[i];
    }
    for(int i=1;i<=lg;i++)for(int j=0;j<n;j++)if(up[j][i-1]!=0)up[j][i]=up[up[j][i-1]][i-1];
    int a,b,ans,m;cin>>m;
    while(m--){
        ans=0;
        cin>>a>>b;
        --a,--b;
        for(int i=lg;i>=0;i--)if(up[a][i]-1<b&&up[a][i])a=up[a][i],ans+=(1ll<<i);
        cout<<ans+1<<'\n';
    }
}
