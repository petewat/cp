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
#include "coin.h"
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define ppii pair<pii,pii>
#define pb push_back
#define mp make_pair
#define rall(x) x.rbegin(),x.rend()
#define all(x) x.begin(),x.end()
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
//#define int long long
const int mxn=2e5+10;
int nl,n;
struct seg{
    int v[4*mxn+10],add[4*mxn+10];
    void init(){for(int i=0;i<=4*mxn+1;i++)v[i]=0,add[i]=0;}
    void push(int pos,int l,int r){
        v[pos]+=add[pos];
        if(l!=r){
            add[pos*2]+=add[pos];
            add[pos*2+1]+=add[pos];
        }
        add[pos]=0;
    }
    void update(int pos,int l,int r,int ql,int qr){
        push(pos,l,r);
        if(l>qr||r<ql)return;
        if(l>=ql&&r<=qr){
            add[pos]=1;
            push(pos,l,r);
            return;
        }
        int mid=l+(r-l)/2;
        update(pos*2,l,mid,ql,qr);
        update(pos*2+1,mid+1,r,ql,qr);
        v[pos]=max(v[pos*2],v[pos*2+1]);
    }
    int qry(int pos,int l,int r,int ql,int qr){
        push(pos,l,r);
        if(l>qr||r<ql)return 0;
        if(l>=ql&&r<=qr)return v[pos];
        int mid=l+(r-l)/2;
        return max(qry(pos*2,l,mid,ql,qr),qry(pos*2+1,mid+1,r,ql,qr));
    }
    void upd(int l,int r){update(1,0,n-1,l,r);}
    int find(int l,int r){return qry(1,0,n-1,l,r);}
}t;
struct iseg{
    int v[2*mxn+10];
    void init(){for(int i=0;i<=2*mxn;i++)v[i]=0;}
    void update(int pos){
        pos+=n;
        v[pos]++;
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
}t2;
vector<pii>ra;
void initialize(int N, vector<int> Rail, int L){
    n=N;
    nl=L;
    for(int i=0;i<N;i++)ra.pb({Rail[i],i});
    sort(rall(ra));
}
vector<int> max_dist(vector<vector<int>>Coins){
    vector<ppii>q;
    for(int i=0;i<Coins.size();i++)q.pb({{Coins[i][2],Coins[i][1]},{Coins[i][0],i}});
    sort(rall(q));
    t2.init();
    t.init();
    int cur=0;
    vector<int>ans(q.size());
    for(int i=0;i<q.size();i++){
        int l=q[i].s.f,r=n-1;
        pii nxt={q[i].s.f,0};
        while(cur<ra.size()&&ra[cur].f>q[i].f.f){
            t2.update(ra[cur].s);
            t.upd(max(0,1+ra[cur].s-nl),ra[cur].s);
            cur++;
        }
        while(l<=r){
            int mid=l+(r-l)/2;
            int k=t2.qry(q[i].s.f,mid);
            if(k<=q[i].f.s){
                if(mid>=nxt.f)nxt={mid,k};
                l=mid+1;
            }
            else r=mid-1;
        }
        int mxtap=t.find(q[i].s.f,nxt.f+1);
        l=q[i].s.f,r=n-1;
        int ca=q[i].s.f-1;
        while(l<=r){
            int mid=l+(r-l)/2;
            if(t2.qry(q[i].s.f,mid)<=nxt.s+mxtap)l=mid+1,ca=max(ca,mid);
            else r=mid-1;
        }
        ca++;
        ans[q[i].s.s]=ca;
    }
    return ans;
}
/*
int main()
{
	int N,Q,L;
    scanf("%d %d %d",&N,&Q,&L);
    std::vector<int>Rail(N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&Rail[i]);
    }
    std::vector<std::vector<int> >Coins(Q,std::vector<int>(3,0));
    for(int i = 0;i < Q;i++)
    {
        scanf("%d %d %d",&Coins[i][0],&Coins[i][1],&Coins[i][2]);
    }
    initialize(N,Rail,L);
	std::vector<int>ans(Q);
	ans = max_dist(Coins);
    for(int i = 0;i < Q;i++)
    {
        printf("%d\n",ans[i]);
    }
}
*/
