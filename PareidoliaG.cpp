#include<iostream>
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
const int mod=1e9+7,mxn=2e5+5,inf=1e9,minf=-1e9,lg=30;
//#undef int
int n,k,m,x,y;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);	
}
int go[mxn+10][6],cost[mxn+10],r[mxn+10],ed[mxn+10];
int suf[mxn+10],val[mxn+10],pref[mxn+10],upd[mxn+10];
string a;
struct node{
    int dp[4][4];
    void init(){for(int i=0;i<4;i++)for(int j=i;j<4;j++)dp[i][j]=minf;}
};
node dummy;
node merge(node a,node b){
    node x;
    for(int i=0;i<4;i++)for(int j=i;j<4;j++){
        x.dp[i][j]=max(b.dp[i][j],a.dp[i][j]);
        for(int k=i;k<j;k++)x.dp[i][j]=max(x.dp[i][j],a.dp[i][k]+b.dp[k+1][j]);
    }
    return x;
}
struct seg{
    node v[4*mxn+10];
    void build(int l,int r,int pos){
        v[pos].init();
        //make "essi"
        if(l==r){
            if(a[l-1]=='e')v[pos].dp[0][0]=cost[l];
            else if(a[l-1]=='s')v[pos].dp[1][1]=v[pos].dp[2][2]=cost[l];
            else if(a[l-1]=='i')v[pos].dp[3][3]=cost[l];
            return;
        }
        int mid=l+(r-l)/2;
        build(l,mid,pos*2);
        build(mid+1,r,pos*2+1);
        v[pos]=merge(v[pos*2],v[pos*2+1]);
    }
    node qry(int l,int r,int pos,int ql,int qr){
        if(l>qr||r<ql)return dummy;
        if(ql<=l&&r<=qr)return v[pos];
        int mid=l+(r-l)/2;
        return merge(qry(l,mid,pos*2,ql,qr),qry(mid+1,r,pos*2+1,ql,qr));
    }
}t;
pii comb(pii a,pii b){
    if(a.f<b.f)a=b;
    else if(a.f==b.f&&a.s>b.s)a=b;
    return a;
}
struct seg2{
    pii v[2*mxn+10];
    void update(int pos,pii val){
        pos+=n;
        v[pos]=comb(v[pos],val);
        for(int i=pos;i>0;i>>=1)v[i>>1]=comb(v[i],v[i^1]);
    }
    pii qry(int l,int r){
        pii ans={0,0};
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if(l&1)ans=comb(ans,v[l++]);
            if(!(r&1))ans=comb(ans,v[r--]);
        }
        return ans;
    }
}t2;
int32_t main(){
    cin>>a;
    dummy.init();
    n=a.size();
    for(int i=1;i<=n;i++){
        cin>>cost[i];
        pref[i]=cost[i]+pref[i-1];
    }
    t.build(1,n,1);
    for(int i=n;i>=1;i--){
        for(int j=0;j<6;j++)go[i][j]=go[i+1][j];
        if(a[i-1]=='b')go[i][0]=i;
        else if(a[i-1]=='e')go[i][1]=go[i][5]=i;
        else if(a[i-1]=='s')go[i][2]=go[i][3]=i;
        else if(a[i-1]=='i')go[i][4]=i;
    }
    for(int i=1;i<=n;i++)if(a[i-1]=='b'){
        int cur=i;
        for(int j=1;j<6;j++){ 
            if(go[cur+1][j]==0){
                cur=-1;
                break;
            }
            cur=go[cur+1][j];
        }
        if(cur==-1)continue;
        r[i]=cur;
        ed[r[i]]=i;
        node x=t.qry(1,n,1,i+1,r[i]-1);
        if(x.dp[0][3]==minf)assert(0);
        val[i]=pref[r[i]-1]-pref[i]-x.dp[0][3];
        if(val[i]<0)assert(0);
    }
    for(int i=1;i<=n;i++)if(r[i]){
        pii x=t2.qry(1,i);
        t2.update(r[i],{x.f+1,x.s+val[i]});
    }
    pii ans=t2.qry(1,n);
    cout<<ans.f<<'\n'<<ans.s<<'\n';
}
/*
compress to range with cost
find max number we can choose for each suffix

mx,mx,mx,mx-1,mx-1,mx-2....,1,0


besgiraffesiebessibessie
1 5 1 1 4 1 3 1 5 1 2 7 6 8 1 5 1 2 5 1 4 1 2 1
b e s b  e s i e  s i  b e  s s i b e  s s b  i e
1 9 3 11 9 7 6 12 8 12 2 12 9 5 5 8 9 14 4 12 15 7 

*/