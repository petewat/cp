#include "werewolf.h"
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
#include <iomanip>  
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
#pragma GCC optimize ("03,unroll-lopps")
const int mxn=7e5,lg=35;
struct kst{
  int pa[mxn+10],cnt=0,val[mxn+10],up[mxn+10][lg+5];
  pii mnmx[mxn+10];
  vector<int>adj[mxn+10],pos;
  void init(){for(int i=0;i<=mxn;i++)pa[i]=i;}
  int find(int u){return (pa[u]==u)?u:pa[u]=find(pa[u]);}
  void merg(int a,int b){
    cnt++;
    int u=find(a),v=find(b);
    adj[cnt].pb(u);
    pa[u]=cnt;
    if(u==v)return;
    adj[cnt].pb(v);
    pa[v]=cnt;
  }
  void dfs(int cur,int n){
    for(auto i:adj[cur])up[i][0]=cur,dfs(i,n);
    if(cur<n)pos.pb(cur);
  }
  void dfs2(int cur){for(auto i:adj[cur])dfs2(i),mnmx[cur]={min(mnmx[cur].f,mnmx[i].f),max(mnmx[cur].s,mnmx[i].s)};}
  void upd(vector<ppii>e,int n){
    cnt=n-1;
    for(auto i:e)merg(i.s.f,i.s.s),val[cnt]=i.f;
    for(int i=0;i<n;i++)val[i]=i;
    dfs(cnt,n);
    for(int i=0;i<n;i++)mnmx[pos[i]]={i,i};
    for(int i=n;i<=cnt;i++)mnmx[i]={1e9,-1e9};
    for(int i=0;i<=lg;i++)up[cnt][i]=cnt;
    for(int j=1;j<=lg;j++)for(int i=0;i<=cnt;i++)up[i][j]=up[up[i][j-1]][j-1];
    dfs2(cnt);
  }
}k[2];
struct fen{
  int bit[mxn+10];
  void update(int pos,int n){for(int i=pos;i<=n;i+=(i&-i))bit[i]++;}
  int qry(int pos){
    int sum=0;
    for(int i=pos;i>0;i-=(i&-i))sum+=bit[i];
    return sum;
  }
}f;
vector<int> check_validity(int n,vector<int>x,vector<int>y,vector<int>st,vector<int>e,vector<int>l,vector<int>r){
  vector<ppii>g;
  for(int i=0;i<x.size();i++)g.pb({min(x[i],y[i]),{x[i],y[i]}});
  sort(rall(g));
  k[0].init();
  k[0].upd(g,n);
  g.clear();
  for(int i=0;i<x.size();i++)g.pb({max(x[i],y[i]),{x[i],y[i]}});
  sort(all(g));
  k[1].init();
  k[1].upd(g,n);
  int cur,cur2;
  vector<pair<pii,pii>>qry;
  for(int i=0;i<st.size();i++){
    cur=st[i];
    for(int j=lg;j>=0;j--)if(k[0].val[k[0].up[cur][j]]>=l[i])cur=k[0].up[cur][j];
    cur2=e[i];
    for(int j=lg;j>=0;j--)if(k[1].val[k[1].up[cur2][j]]<=r[i])cur2=k[1].up[cur2][j];
    qry.pb({{k[0].mnmx[cur].f-1,i+1},k[1].mnmx[cur2]});
    qry.pb({{k[0].mnmx[cur].s,-(i+1)},k[1].mnmx[cur2]});
  }
  vector<int>ans(st.size());
  sort(all(qry));
  int id,mul=1;
  cur=0;
  for(int i=0;i<qry.size();i++){
    if(qry[i].f.s>0)id=qry[i].f.s-1,mul=-1;
    else id=-(qry[i].f.s)-1,mul=1;
    while(cur<=qry[i].f.f)f.update(k[1].mnmx[k[0].pos[cur]].f+1,n),cur++;
    ans[id]+=((f.qry(qry[i].s.s+1)*mul)-(f.qry(qry[i].s.f)*mul));
  }
  for(auto &i:ans)i=!!i;
  return ans;
  /*
  range l1,r2 l2,r2
  find how many on from 1->l2-1,and 1->r2
  find on 1->x; for qry i;
  foreach qry l1,r1; sort(all) l1,r1
  to get x when l1,r1 is on is (1->x when r1)-(1->x when l1-1);
  */
}
