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
#include <cstdlib> 
#include <cstdint>
using namespace std;
#define ll long long
#define f first
//#define endl "\n"
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
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
//#define int long long
//#define double long double
const int mxn=6e5,inf=1e9,minf=-1e9,Mxn=1e7+1;
int mx;
int del[Mxn];
set<int>pos[mxn+10];
int cnt=0;
int curid=0;
vector<int>comp;
int n,k,q;
struct seg{
    priority_queue<pii>v[2*mxn+10];
    priority_queue<pii>v2[2*mxn+10];
    void update(int l,int r,pii val,int type){//lazy on top, 1=right
        l=max(l,0);
        r=max(r,l);
        for(l+=mx,r+=mx;l<=r;l>>=1,r>>=1){
            if(l&1){
                if(type)v[l].push(val);
                else v2[l].push(val);
                l++;
            }
            if(!(r&1)){
                if(type)v[r].push(val);
                else v2[r].push(val);
                r--;
            }
        }
    }
    pii qry(int pos){
        int g=comp.size()-1;
        pos=min(pos,g);
        pii ans={minf,minf};
        for(pos+=mx;pos>=0;pos>>=1){
            while(!v[pos].empty()&&del[v[pos].top().s])v[pos].pop();
            if(v[pos].size())ans.f=max(ans.f,v[pos].top().f);
            while(!v2[pos].empty()&&del[v2[pos].top().s])v2[pos].pop();
            if(v2[pos].size())ans.s=max(ans.s,v2[pos].top().f);
            if(pos==0)break;
        }
        return ans;
    }
}seg;
int rangeleft[mxn+10],rangeright[mxn+10];
int rangeidleft[mxn+10],rangeidright[mxn+10];
int idpos[mxn+10],idposincomp[mxn+10],tmp;
void add(int x,int t){
    auto it=pos[t].insert(x).f;
    if(it!=pos[t].begin()){
        it--;
        tmp=(*it);
        int val=ceil((idpos[tmp]+idpos[x])*1.0/2);
        //find mid point
        auto it2=lb(all(comp),val)-comp.begin();
        if(it2==comp.size())assert(0);
        //find mid point in comp
        if(it2<=idposincomp[tmp])it2=idposincomp[tmp]+1;
        rangeright[tmp]=it2-1;
        if(it2>idposincomp[x])rangeleft[x]=idposincomp[x];
        else rangeleft[x]=it2;
        del[rangeidright[tmp]]=1;
        rangeidright[tmp]=++curid;
        rangeidleft[x]=++curid;
        seg.update(idposincomp[tmp],rangeright[tmp],{-idpos[tmp],rangeidright[tmp]},1);
        it++;
    }
    else{
        rangeleft[x]=0;
        rangeidleft[x]=++curid;
    }
    it++;
    if(it!=pos[t].end()){
        tmp=(*it);
        int val=ceil((idpos[tmp]+idpos[x])*1.0/2);
        auto it2=lb(all(comp),val)-comp.begin();
        if(it2==comp.size())assert(0);
        if(it2<=idposincomp[x])it2=idposincomp[x]+1;
        rangeright[x]=it2-1;
        rangeleft[tmp]=it2;
        if(it2>idposincomp[tmp])rangeleft[tmp]=idposincomp[tmp];
        else rangeleft[tmp]=it2;
        del[rangeidleft[tmp]]=1;
        rangeidright[x]=++curid;
        rangeidleft[tmp]=++curid;
        seg.update(rangeleft[tmp],idposincomp[tmp],{idpos[tmp],rangeidleft[tmp]},0);
    }
    else{
        rangeright[x]=mx;
        rangeidright[x]=++curid;
    }
    seg.update(rangeleft[x],idposincomp[x],{idpos[x],rangeidleft[x]},0);
    seg.update(idposincomp[x],rangeright[x],{-idpos[x],rangeidright[x]},1);
}
void die(int x,int t){
    del[rangeidleft[x]]=1;
    del[rangeidright[x]]=1;
    auto it=pos[t].find(x);
    if(it==pos[t].end())assert(0);
    int l,r;
    if(it==pos[t].begin()){
        it++;
        if(it!=pos[t].end()){
            tmp=(*it);
           seg.update(0,rangeleft[tmp]-1,{idpos[tmp],rangeidleft[tmp]},0);
           rangeleft[tmp]=0;
        }
        it--;
        pos[t].erase(it);
        return;
    }
    it--;
    l=(*it);
    it++;
    it++;
    if(it==pos[t].end()){
        if(rangeright[l]!=mx)seg.update(rangeright[l]+1,mx,{-idpos[l],rangeidright[l]},1);
        rangeright[l]=mx;
        it--;
        pos[t].erase(it);
        return;
    }
    else r=(*it);
    int val=ceil((idpos[l]+idpos[r])*1.0/2);
    auto it2=lb(all(comp),val)-comp.begin();
    if(it2==comp.size())assert(0);
    int k=it2;
    if(rangeright[l]>=it2)k=rangeright[l]+1;
    seg.update(rangeright[l],k-1,{-idpos[l],rangeidright[l]},1);
    if(rangeleft[r]<k)k=rangeleft[r];
    seg.update(k,rangeleft[r],{idpos[r],rangeidleft[r]},0);
    rangeright[l]=k-1;
    rangeleft[r]=k;
    it--;
    pos[t].erase(it);
    return;
}
int ans[mxn+10];
struct info{int time,etype,pos,type,id;};
bool cmp(info a,info b){
    if(a.pos==b.pos)return a.etype>b.etype;
    return a.pos<b.pos;
}
bool cmp2(info a,info b){
    if(a.time==b.time)return a.etype<b.etype;
    return a.time<b.time;
}
vector<info>event;
int what[mxn+10];
int32_t main(){
    fastio
    cin>>n>>k>>q;
    for(int i=0;i<n;i++){
        int x,t,a,b;cin>>x>>t>>a>>b;
        event.pb({a,1,x,t,i});
        event.pb({b+1,0,x,t,i});
        comp.pb(x);
    }
    vector<pair<pii,int>>qry(q);
    for(int i=0;i<q;i++)cin>>qry[i].f.s>>qry[i].f.f,qry[i].s=i,comp.pb(qry[i].f.s);
    sort(all(qry));
    sort(all(event),cmp);
    sort(all(comp));
    comp.erase(unique(all(comp)),comp.end());
    int cnt=0;
    for(auto &i:event){
        if(i.etype==0){
            i.id=what[i.id];
            continue;
        }
        what[i.id]=cnt;
        i.id=cnt;
        idpos[cnt]=i.pos;
        idposincomp[cnt]=lb(all(comp),i.pos)-comp.begin();
        cnt++;
    }
    sort(all(event),cmp2);
    int p=cnt;
    mx=comp.size();
    int cur=0,g=0;
    cnt=0;
    for(auto i:qry){
        g++;
        while(cur<event.size()&&event[cur].time<=i.f.f){
            if(event[cur].etype){
                if(pos[event[cur].type].size()==0)cnt++;
                add(event[cur].id,event[cur].type);
            }
            else{
                die(event[cur].id,event[cur].type);
                if(pos[event[cur].type].size()==0)cnt--;
            }
            cur++;
        }
        pii bru=seg.qry(lb(all(comp),i.f.s)-comp.begin());
        if(cnt!=k)ans[i.s]=-1;
        else{
            if(bru.f!=minf)ans[i.s]=max(ans[i.s],i.f.s+bru.f);
            if(bru.s!=minf)ans[i.s]=max(ans[i.s],bru.s-i.f.s);
        }
    }
    for(int i=0;i<q;i++)cout<<ans[i]<<'\n';
	return 0;
}

/*
(2*n+q)log(n)*log(10^8)
when there are currently a,b,c shop active with the same k
int range of each shop will be (0,(a+b)/2),((a+b)/2+1,(b+c)/2),((b+c)/2+1,mx)
the contribution on range l,r when shop pos is x will be
x-a,x-b,x,c-x,d-x;
we can keep muliset segtree
*/